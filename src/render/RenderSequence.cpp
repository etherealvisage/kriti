#include <GL/glew.h>

#include "RenderSequence.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw() {
    m_meshVAO->bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferID);
    m_technique->activate();
    //m_techniqueParams->set();

    glDrawElements(GL_TRIANGLES, m_elements.size(), GL_UNSIGNED_INT,
        (void *)0);
}

void RenderSequence::generateBuffer() {
    glGenBuffers(1, &m_elementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elements.size()*sizeof(int),
        &m_elements[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}  // namespace Render
}  // namespace Kriti
