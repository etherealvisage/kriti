#include <vector>

#include "TextRenderer.h"

#include "render/RenderableFactory.h"

#include "MessageSystem.h"

namespace Kriti {
namespace GUI {

boost::shared_ptr<Render::Renderable> TextRenderer::render(
    boost::shared_ptr<Font> font, std::string s) {

    std::vector<Math::Vector> vertices;
    std::vector<Math::Vector> normals;
    std::vector<Math::Vector> texCoords;

    std::vector<unsigned int> indices;

    Math::Vector cursor;
    for(char c : s) {
        Font::CharSpec cs;
        if(!font->getCharSpec((int)c, cs)) continue;
        Math::Vector off(cs.xoff, cs.yoff);
        Math::Vector w(cs.w);
        Math::Vector h(0,cs.h);

        indices.push_back(vertices.size());
        vertices.push_back(cursor + off);
        indices.push_back(vertices.size());
        vertices.push_back(cursor + off - h);
        indices.push_back(vertices.size());
        vertices.push_back(cursor + off + w - h);
        indices.push_back(vertices.size());
        vertices.push_back(cursor + off + w);

        Math::Vector tc(cs.x, cs.y);
        texCoords.push_back(tc);
        texCoords.push_back(tc + h);
        texCoords.push_back(tc + w + h);
        texCoords.push_back(tc + w);

        for(int i = 0; i < 4; i ++) normals.push_back(Math::Vector());

        cursor += Math::Vector(cs.xadv);
    }

    return Render::RenderableFactory().fromQuadGeometry(vertices, normals,
        texCoords, indices, font->materialName());
}

}  // namespace GUI
}  // namespace Kriti
