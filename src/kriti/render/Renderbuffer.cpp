#include <GL/glew.h>

#include "Renderbuffer.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

Renderbuffer::Renderbuffer(Type type, int width, int height, int samples)
    : m_type(type), m_width(width), m_height(height), m_samples(samples) {

    ErrorTracker::trackFrom("Renderbuffer constructor (before all)");
    glGenRenderbuffers(1, &m_id);
    ErrorTracker::trackFrom("Renderbuffer constructor (after generation)");

    glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    ErrorTracker::trackFrom("Renderbuffer constructor (after bind)");

    GLenum format;
    switch(m_type) {
    case Colour:
        format = GL_RGBA32F;
        break;
    case Depth:
        format = GL_DEPTH_COMPONENT32F;
        break;
    default:
        Message3(Render, Fatal,
            "Unknown Renderbuffer::Type passed to constructor");
    }

    glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_samples, format,
        m_width, m_height);
    ErrorTracker::trackFrom("Renderbuffer constructor (after storage)");

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    ErrorTracker::trackFrom("Renderbuffer constructor (after clear)");
}

Renderbuffer::~Renderbuffer() {
    glDeleteRenderbuffers(1, &m_id);
    ErrorTracker::trackFrom("Renderbuffer destructor (after delete)");
}

}  // namespace Render
}  // namespace Kriti
