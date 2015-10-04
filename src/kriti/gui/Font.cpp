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

    // first pass
    int texWidth = 0, texHeight = 0;
    for(int c = 0; c < m_face->num_glyphs; c ++) {
        int error = FT_Load_Glyph(m_face, c, FT_LOAD_DEFAULT | FT_LOAD_RENDER);
        if(error) { Message3(GUI, Fatal, "Couldn't load glyph!"); }
        texWidth += m_face->glyph->bitmap.width;
        texWidth ++; // spacing
        texHeight = std::max(texHeight, (int)m_face->glyph->bitmap.rows);
    }

    Message3(GUI, Debug, "Texture size: " << texWidth << "x" << texHeight);

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
        cs.x = xoff/(double)texWidth;
        cs.y = 0.0;
        cs.w = m_face->glyph->bitmap.width/(double)texWidth;
        cs.h = m_face->glyph->bitmap.rows/(double)texHeight;
        cs.xoff = m_face->glyph->bitmap_left;
        cs.yoff = -m_face->glyph->bitmap_top;
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

    {
        std::ofstream file("output.pgm");
        file << "P2" << std::endl;
        file << texWidth << " " << texHeight << std::endl;
        file << 255 << std::endl;
        for(int i = 0; i < texHeight; i ++) {
            for(int j = 0; j < texWidth; j ++) {
                file << (int)(data[i*texWidth + j]*255) << " ";
            }
            file << std::endl;
        }
    }

    delete[] data;
}

void Font::Instance::getCharSpec(int c, Font::CharSpec &cs) {
    int index = FT_Get_Char_Index(m_face, c);
    cs = m_chars[index];
}

bool Font::loadFrom(std::string identifier) {
#if 0
    /*
    Message3(GUI, Debug, "Loading font \"" << identifier << "\"");
    const pugi::xml_node &fontNode =
        ResourceRegistry::get<XMLResource>(
        "data")->doc().first_element_by_path(
        "/kriti/fonts").find_child_by_attribute(
        "font", "name", identifier.c_str());
    */

    m_materialName = fontNode.child("material").text().as_string("");

    if(m_materialName == "") return false;

    std::string desc_name = fontNode.child("description").text().as_string("");

    auto desc = ResourceRegistry::get<FileResource>(  
        "fonts/" + desc_name + ".txt");
    if(!desc) return false;

    std::istringstream iss(desc->fileContent());

    int texture_width
        = fontNode.child("texture").attribute("width").as_int(0);
    int texture_height
        = fontNode.child("texture").attribute("height").as_int(0);

    int id;
    CharSpec cs;
    while(iss >> id >> cs.x >> cs.y >> cs.w >> cs.h >> cs.xoff >> cs.yoff
        >> cs.xadv) {

        cs.x /= texture_width;
        cs.w /= texture_width;
        cs.xoff /= texture_width;
        cs.xadv /= texture_width;
        cs.y /= texture_height;
        cs.h /= texture_height;
        cs.yoff /= texture_height;
        m_chars[id] = cs;
    }

#endif
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

    Message3(GUI, Debug, "Font height: " << m_fontHeight);

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
