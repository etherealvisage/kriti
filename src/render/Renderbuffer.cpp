#include <GL/glew.h>

#include "Renderbuffer.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Renderbuffer::Renderbuffer(Type type, int width, int height, int samples)
    : m_type(type), m_width(width), m_height(height), m_samples(samples) {

    glGenRenderbuffers(1, &m_id);

    glBindRenderbuffer(GL_RENDERBUFFER, m_id);

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

    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Renderbuffer::~Renderbuffer() {
    glDeleteRenderbuffers(1, &m_id);
}

}  // namespace Render
}  // namespace Kriti
