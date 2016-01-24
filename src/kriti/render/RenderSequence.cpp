#include "../ogl.h"

#include <boost/weak_ptr.hpp>

#include "RenderSequence.h"
#include "TextureContext.h"
#include "ErrorTracker.h"

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
        type = gl::LINES;
        break;
    case Triangles:
        Profile::Tracker::instance()->addToCounter("Triangles",
            (m_end-m_start+1)/3);
        type = gl::TRIANGLES;
        break;
    default:
        Message3(Render, Fatal, "Unknown type in RenderSequence");
        break;
    }
    ErrorTracker::trackFrom("RenderSequence draw (before all)");
    if(m_mode == Indexed) {
        gl::DrawElements(type, m_end-m_start+1, gl::UNSIGNED_INT,
            (void *)(sizeof(unsigned int)*m_start));
        ErrorTracker::trackFrom("RenderSequence draw (after drawElements)");
    }
    else if(m_mode == Sequential) {
        gl::DrawArrays(type, m_start, m_end-m_start+1);
        ErrorTracker::trackFrom("RenderSequence draw (after drawArrays)");
    }
}

}  // namespace Render
}  // namespace Kriti
