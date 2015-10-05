#include <sstream>

#include <fstream>

#include <boost/make_shared.hpp>

#include "Font.h"
#include "Scale.h"

#include "../render/Texture.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"
#include "../FileResource.h"
#include "../XMLResource.h"

namespace Kriti {
namespace GUI {

FT_Library getFTLibrary() {
    static FT_Library library = nullptr;
    if(!library) {
        FT_Init_FreeType(&library);
    }
    return library;
}

Font::Instance::Instance(FT_Face face, std::vector<FT_Glyph_Metrics> &sizes,
    int ptSize) : m_face(face), m_sizes(sizes), m_ptSize(ptSize) {

    Scale s;
    int error = FT_Set_Char_Size(m_face, 0, ptSize*64, s.xDPI(), s.yDPI());
    if(error) {
        Message3(GUI, Fatal, "Couldn't set char size to " << ptSize);
    }

    if(m_face->num_glyphs > 100) m_face->num_glyphs = 100;

    // first pass
    int texWidth = 0, texHeight = 0;
    for(int c = 0; c < m_face->num_glyphs; c ++) {
        int error = FT_Load_Glyph(m_face, c, FT_LOAD_DEFAULT | FT_LOAD_RENDER);
        if(error) { Message3(GUI, Fatal, "Couldn't load glyph!"); }
        texWidth += m_face->glyph->bitmap.width;
        texWidth ++; // spacing
        texHeight = std::max(texHeight, (int)m_face->glyph->bitmap.rows);
    }

    float *data = new float[texWidth*texHeight];
    for(int i = 0; i < texWidth*texHeight; i ++) data[i] = 0;

    int xoff = 0;
    for(int c = 0; c < m_face->num_glyphs; c ++) {
        int error = FT_Load_Glyph(m_face, c, FT_LOAD_DEFAULT | FT_LOAD_RENDER);
        if(error) { Message3(GUI, Fatal, "Couldn't load glyph!"); }

        unsigned char *img = m_face->glyph->bitmap.buffer;
        for(int r = 0; r < m_face->glyph->bitmap.rows; r ++) {
            for(int c = 0; c < m_face->glyph->bitmap.width; c ++) {
                data[r*texWidth + xoff+c] = img[c]/255.0;
            }
            img += m_face->glyph->bitmap.pitch;
        }

        CharSpec cs;
        cs.tx = xoff/(double)texWidth;
        cs.ty = 0.0;
        cs.tw = m_face->glyph->bitmap.width/(double)texWidth;
        cs.th = m_face->glyph->bitmap.rows/(double)texHeight;
        cs.sw = Scale().fromPixelsX(m_face->glyph->bitmap.width);
        cs.sh = Scale().fromPixelsY(m_face->glyph->bitmap.rows);
        cs.xoff = Scale().fromPixelsX(m_face->glyph->bitmap_left);
        cs.yoff = Scale().fromPixelsY(-m_face->glyph->bitmap_top);
        cs.xadv = Scale().fromPixelsX(m_face->glyph->metrics.horiAdvance/64);
        cs.yadv = Scale().fromPixelsY(m_face->glyph->metrics.vertAdvance/64);

        m_chars.push_back(cs);

        xoff += m_face->glyph->bitmap.width;
        xoff ++; // spacing
    }

    m_latestTexture =
        boost::make_shared<Render::Texture>(Render::Texture::ColourR,
            Render::Texture::Simple, texWidth, texHeight);

    m_latestTexture->reset(texWidth, texHeight, data);

    delete[] data;
}

void Font::Instance::getCharSpec(int c, Font::CharSpec &cs) {
    int index = FT_Get_Char_Index(m_face, c);
    cs = m_chars[index];
}

bool Font::loadFrom(std::string identifier) {
    auto fontfile = ResourceRegistry::get<FileResource>(identifier);
    if(!fontfile) return false;

    auto content = fontfile->fileContent();
    int error = FT_New_Memory_Face(getFTLibrary(),
        reinterpret_cast<const FT_Byte *>(content.data()), content.length(), 0,
        &m_face);

    if(error) return false;

    m_fontHeight = 0;

    for(int i = 0; i < m_face->num_glyphs; i ++) {
        // Make this not render the glyph?
        FT_Load_Glyph(m_face, i, FT_LOAD_DEFAULT | FT_LOAD_NO_SCALE);
        m_fontHeight = std::max(m_fontHeight,
            (int)m_face->glyph->metrics.height);
        m_sizes.push_back(m_face->glyph->metrics);
    }

    return true;
}

boost::shared_ptr<Font::Instance> Font::getInstance(int ptSize) {
    if(!m_instances.count(ptSize)) {
        auto ins = m_instances[ptSize] =
            boost::shared_ptr<Font::Instance>(new Instance(m_face, m_sizes,
                ptSize));
    }
    
    return m_instances[ptSize];
}

}  // namespace GUI
}  // namespace Kriti
