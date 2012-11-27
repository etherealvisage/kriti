#ifndef KRITI_RENDER__RENDER_SEQUENCE_H
#define KRITI_RENDER__RENDER_SEQUENCE_H

#include "Technique.h"
#include "VAO.h"

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class RenderSequence {
private:
    boost::shared_ptr<Technique> m_technique;
    int m_start, m_end;
    boost::shared_ptr<VAO> m_vao;
public:
    RenderSequence(boost::shared_ptr<Technique> technique,
        boost::shared_ptr<VAO> vao, int start, int end)
        : m_technique(technique), m_start(start), m_end(end), m_vao(vao) {}

    void draw(const Math::Matrix &projection,
        const Math::Matrix &modelTransformation);
};

}  // namespace Render
}  // namespace Kriti

#endif
