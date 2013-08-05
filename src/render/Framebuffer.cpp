#include <GL/glew.h>

#include "Framebuffer.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &m_id);

    // mark all as not in use
    for(int i = 0; i < Attachments; i ++) {
        m_textures[i].first = m_rbuffers[i].first = false;
    }
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_id);
}

void Framebuffer::attach(Attachment where,
    boost::shared_ptr<Texture> texture) {

    m_textures[where].first = true;
    m_textures[where].second = texture;

    m_rbuffers[where].first = false;
    m_rbuffers[where].second = boost::shared_ptr<Renderbuffer>();
}

void Framebuffer::attach(Attachment where,
    boost::shared_ptr<Renderbuffer> rbuffer) {

    m_rbuffers[where].first = true;
    m_rbuffers[where].second = rbuffer;

    m_textures[where].first = false;
    m_textures[where].second = boost::shared_ptr<Texture>();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, convert(where),
        GL_RENDERBUFFER, rbuffer->id());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void Framebuffer::bindRead() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_id);
}

void Framebuffer::bindWrite() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_id);
}

GLenum Framebuffer::convert(Attachment where) {
    switch(where) {
    case DepthBuffer:
        return GL_DEPTH_ATTACHMENT;
    case ColourBuffer0:
        return GL_COLOR_ATTACHMENT0;
    case ColourBuffer1:
        return GL_COLOR_ATTACHMENT1;
    case ColourBuffer2:
        return GL_COLOR_ATTACHMENT2;
    case ColourBuffer3:
        return GL_COLOR_ATTACHMENT3;
    default:
        Message3(Render, Fatal,
            "Unknown Framebuffer::Attachment passed to convert.");
        break;
    }

    // make GCC quiet, even though the default branch abort()s.
    return GL_INVALID_VALUE;
}

}  // namespace Render
}  // namespace Kriti
