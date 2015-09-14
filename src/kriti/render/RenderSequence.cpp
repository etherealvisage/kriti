#include <GL/glew.h>

#include <boost/weak_ptr.hpp>

#include "RenderSequence.h"
#include "TextureContext.h"

#include "../profile/Tracker.h"

#include "../MessageSystem.h"
#include "../TimeValue.h"

namespace Kriti {
namespace Render {

void RenderSequence::draw(const Uniforms &params,
    std::map<boost::weak_ptr<Material>, Uniforms> &materialParams,
    const Math::Matrix &modelTransformation) {

    m_vao->bind();
    auto program = m_material->program();
    program->activate();
    m_material->params().set(program);
    program->setUniform("model", m_sequenceTransform * modelTransformation);
    m_extraParams.set(program);

    materialParams[m_material].set(program);

    params.set(program);

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
