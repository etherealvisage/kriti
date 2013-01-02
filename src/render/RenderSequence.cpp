#include <GL/glew.h>

#include "RenderSequence.h"

#include "MessageSystem.h"
#include "TimeValue.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw(const Math::Matrix &projection,
    const Math::Matrix &modelTransformation) {

    m_vao->bind();
    m_technique->activate();
    m_technique->setUniform("camera", projection);
    m_technique->setUniform("model", modelTransformation);
    static TimeValue start = TimeValue::current();
    m_technique->setUniform("g_time", (TimeValue::current() - start).toMsec());

    //Message3(Render, Debug, "Drawing " << m_end-m_start+1 << " vertices!");
    GLenum type;
    switch(m_type) {
    case Lines:
        type = GL_LINES;
        break;
    case Triangles:
        type = GL_TRIANGLES;
        break;
    case Quads:
        type = GL_QUADS;
        break;
    }
    glDrawElements(type, m_end-m_start+1, GL_UNSIGNED_INT,
        (void *)(sizeof(unsigned int)*m_start));
}

}  // namespace Render
}  // namespace Kriti
