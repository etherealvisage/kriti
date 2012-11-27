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

    /*int count = m_end-m_start+1;
    int elemData[count];
    glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
        count*4,
        sizeof(unsigned int)*(m_end-m_start+1), (void *)elemData);
    Message3(Render, Debug, count << " indices.");
    for(int i = 0; i < count; i ++) {
        Message3(Render, Debug, "    [" << i << "]: " << elemData[i]);
    }*/
    glDrawElements(GL_TRIANGLES, m_end-m_start+1, GL_UNSIGNED_INT,
        (void *)(sizeof(unsigned int)*m_start));
    /*Message3(Render, Debug, "drawing [" << m_start << "," << m_end << "]");*/
    /*glDrawArrays(GL_TRIANGLES, m_start, m_end-m_start+1);*/
}

}  // namespace Render
}  // namespace Kriti
