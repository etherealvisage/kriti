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

    Math::Vector cursor;
    for(char c : s) {
        Font::CharSpec cs;
        font->getCharSpec((int)c, cs);
        Math::Vector off(cs.xoff, cs.yoff);
        Math::Vector w(cs.w);
        Math::Vector h(0,cs.h);

        indices.push_back(vertices.size());
        vertices.push_back((cursor + off) * scale);
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off - h) * scale);
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off + w - h) * scale);
        indices.push_back(vertices.size());
        vertices.push_back((cursor + off + w) * scale);

        Math::Vector tc(cs.x, cs.y);
        texCoords.push_back(tc);
        texCoords.push_back(tc + h);
        texCoords.push_back(tc + w + h);
        texCoords.push_back(tc + w);

        for(int i = 0; i < 4; i ++) normals.push_back(Math::Vector());

        cursor += Math::Vector(cs.xadv);
    }

    auto ret = Render::RenderableFactory().fromQuadGeometry(vertices, normals,
        texCoords, indices, "gui_text");

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
        Math::Vector w(cs.w);
        Math::Vector h(0,cs.h);

        minY = std::min(minY, cs.yoff - cs.h);
        maxY = std::max(maxY, cs.yoff);

        width += cs.xadv;
    }

    ul = Math::Vector(0.0, minY);
    lr = Math::Vector(width, maxY);
}

}  // namespace GUI
}  // namespace Kriti
