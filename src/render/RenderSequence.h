#ifndef KRITI_RENDER__RENDER_SEQUENCE_H
#define KRITI_RENDER__RENDER_SEQUENCE_H

#include "Technique.h"
#include "VAO.h"

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class RenderSequence {
public:
    enum RenderType {
        Lines,
        Triangles,
        Quads
    };
private:
    boost::shared_ptr<Technique> m_technique;
    int m_start, m_end;
    boost::shared_ptr<VAO> m_vao;
    RenderType m_type;
public:
    RenderSequence(boost::shared_ptr<Technique> technique,
        boost::shared_ptr<VAO> vao, int start, int end,
        RenderType type = Triangles) : m_technique(technique),
        m_start(start), m_end(end), m_vao(vao), m_type(type) {}

    void draw(const Math::Matrix &projection,
        const Math::Matrix &modelTransformation);
};

}  // namespace Render
}  // namespace Kriti

#endif
