#include <GL/glew.h>

#include "RenderSequence.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw(const Math::Matrix &projection,
    const Math::Matrix &modelTransformation) {

    m_vao->bind();
    m_technique->activate();
    m_technique->setUniform("camera", projection);
    m_technique->setUniform("model", modelTransformation);

    glDrawElements(GL_TRIANGLES, m_end-m_start+1, GL_UNSIGNED_INT,
        (void *)(sizeof(unsigned int)*m_start));
}

}  // namespace Render
}  // namespace Kriti
