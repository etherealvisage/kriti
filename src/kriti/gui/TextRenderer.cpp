#include <vector>

#include "TextRenderer.h"

#include "../render/RenderableFactory.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

std::vector<TextRenderer::Block> blockify(std::string text,
    TextRenderer::BlockifyMode mode) {
    
    std::vector<TextRenderer::Block> blocks;

    switch(mode) {
    case TextRenderer::Simple: {
        std::string::size_type cursor = 0, next = std::string::npos;
        do {
            next = text.find(" ", cursor+1);
            blocks.push_back(TextRenderer::Block(text.substr(cursor, next),
                0.0));
            cursor = next;
        } while(cursor != std::string::npos);
        break;
    }
    default:
        Message3(GUI, Fatal, "Unknown blockify mode!");
        break;
    }

    return blocks;
}

boost::shared_ptr<Render::Renderable> TextRenderer::renderString(
    boost::shared_ptr<Font::Instance> font, std::string s, Math::Vector scale) {

    std::vector<Math::Vector> vertices;
    std::vector<Math::Vector> normals;
    std::vector<Math::Vector> texCoords;

    std::vector<unsigned int> indices;

    Message3(GUI, Debug, "GL error (0): " << glGetError());
    Message3(GUI, Debug, "Text scale: " << scale.toString());

    Math::Vector cursor;
    for(char c : s) {
        Font::CharSpec cs;
        font->getCharSpec((int)c, cs);
        Math::Vector off(cs.xoff, cs.yoff);
        Math::Vector sw(cs.sw,0);
        Math::Vector sh(0,cs.sh);

        indices.push_back(vertices.size());
        vertices.push_back((cursor + off) * scale);
        Message3(GUI, Debug, "Vertex 0: " << vertices.back().toString());
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off - sh) * scale);
        Message3(GUI, Debug, "Vertex 1: " << vertices.back().toString());
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off + sw - sh) * scale);
        Message3(GUI, Debug, "Vertex 2: " << vertices.back().toString());
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off + sw) * scale);
        Message3(GUI, Debug, "Vertex 3: " << vertices.back().toString());

        Math::Vector tc(cs.tx, cs.ty);
        Math::Vector tw(cs.tw, 0);
        Math::Vector th(0, cs.th);
        texCoords.push_back(tc);
        Message3(GUI, Debug, "TVertex 0: " << texCoords.back().toString());
        texCoords.push_back(tc + th);
        Message3(GUI, Debug, "TVertex 1: " << texCoords.back().toString());
        texCoords.push_back(tc + tw + th);
        Message3(GUI, Debug, "TVertex 2: " << texCoords.back().toString());
        texCoords.push_back(tc + tw);
        Message3(GUI, Debug, "TVertex 3: " << texCoords.back().toString());

        for(int i = 0; i < 4; i ++) normals.push_back(Math::Vector());

        cursor += Math::Vector(cs.xadv);
    }

    Message3(GUI, Debug, "GL error (1): " << glGetError());

    auto ret = Render::RenderableFactory().fromQuadGeometry(vertices, normals,
        texCoords, indices, "gui_text");

    Message3(GUI, Debug, "GL error (2): " << glGetError());

    ret->renderSequence(0)->extraParams().setParam("u_tex", font->texture());

    return ret;
}

void TextRenderer::sizeString(boost::shared_ptr<Font::Instance> font,
    std::string s, Math::Vector &ul, Math::Vector &lr) {

    double width = 0.0;
    double minY = 0.0, maxY = 0.0;

    for(char c : s) {
        Font::CharSpec cs;
        font->getCharSpec((int)c, cs);

        Math::Vector off(cs.xoff, cs.yoff);
        Math::Vector w(cs.sw);
        Math::Vector h(0,cs.sh);

        minY = std::min(minY, cs.yoff - cs.sh);
        maxY = std::max(maxY, cs.yoff);

        width += cs.xadv;
    }

    ul = Math::Vector(0.0, minY);
    lr = Math::Vector(width, maxY);
}

}  // namespace GUI
}  // namespace Kriti
