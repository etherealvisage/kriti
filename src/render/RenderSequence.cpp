#include <GL/glew.h>

#include "RenderSequence.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw() {
    m_vao->bind();
    m_technique->activate();
    //m_techniqueParams->set();

    glDrawElements(GL_TRIANGLES, m_end-m_start+1, GL_UNSIGNED_INT,
        (void *)(sizeof(int)*m_start));
}

}  // namespace Render
}  // namespace Kriti
