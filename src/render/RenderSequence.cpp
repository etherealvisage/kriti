#include <GL/glew.h>

#include "RenderSequence.h"
#include "TextureContext.h"

#include "profile/Tracker.h"

#include "MessageSystem.h"
#include "TimeValue.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw(const TechniqueParams &params,
    boost::shared_ptr<TextureContext> textureContext,
    const Math::Matrix &modelTransformation) {

    m_vao->bind();
    auto technique = m_material->technique();
    technique->activate(textureContext);
    m_material->params().set(technique);
    technique->setUniform("model", modelTransformation);
    m_materialParams.set(technique);
    params.set(technique);

    GLenum type;
    switch(m_type) {
    case Lines:
        type = GL_LINES;
        break;
    case Triangles:
        Profile::Tracker::instance()->addToCounter("Triangles",
            (m_end-m_start+1)/3);
        type = GL_TRIANGLES;
        break;
    default:
        Message3(Render, Fatal, "Unknown type in RenderSequence");
        break;
    }
    if(m_mode == Indexed) {
        glDrawElements(type, m_end-m_start+1, GL_UNSIGNED_INT,
            (void *)(sizeof(unsigned int)*m_start));
    }
    else if(m_mode == Sequential) {
        glDrawArrays(type, m_start, m_end-m_start+1);
    }
}

}  // namespace Render
}  // namespace Kriti
