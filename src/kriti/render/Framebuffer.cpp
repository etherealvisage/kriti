#include "../ogl.h"

#include "Framebuffer.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

Framebuffer::Framebuffer() {
    ErrorTracker::trackFrom("Framebuffer constructor (before all)");
    gl::GenFramebuffers(1, &m_id);
    ErrorTracker::trackFrom("Framebuffer constructor (after gen)");

    // mark all as not in use
    for(int i = 0; i < Attachments; i ++) {
        m_textures[i].first = m_rbuffers[i].first = false;
    }
}

Framebuffer::~Framebuffer() {
    ErrorTracker::trackFrom("Framebuffer destructor (before all)");
    gl::DeleteFramebuffers(1, &m_id);
    ErrorTracker::trackFrom("Framebuffer destructor (after del)");
}

void Framebuffer::attach(Attachment where,
    boost::shared_ptr<Texture> texture) {

    m_textures[where].first = true;
    m_textures[where].second = texture;

    m_rbuffers[where].first = false;
    m_rbuffers[where].second = boost::shared_ptr<Renderbuffer>();

    ErrorTracker::trackFrom("Framebuffer texture attach (before all)");
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_id);
    ErrorTracker::trackFrom("Framebuffer texture attach (after bind)");
    // TODO: support levels other than zero.
    // TODO: support targets other than GL_TEXTURE_2D{,MULTISAMPLE}
    GLenum type = gl::TEXTURE_2D;
    if(texture->samples() != 0) type = gl::TEXTURE_2D_MULTISAMPLE;
    gl::FramebufferTexture2D(gl::DRAW_FRAMEBUFFER, convert(where),
        type, texture->id(), 0);

    ErrorTracker::trackFrom("Framebuffer texture attach (after texture)");
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, 0);
    ErrorTracker::trackFrom("Framebuffer texture attach (after clear)");
}

void Framebuffer::attach(Attachment where,
    boost::shared_ptr<Renderbuffer> rbuffer) {

    m_rbuffers[where].first = true;
    m_rbuffers[where].second = rbuffer;

    m_textures[where].first = false;
    m_textures[where].second = boost::shared_ptr<Texture>();

    ErrorTracker::trackFrom("Framebuffer renderbuffer attach (before all)");
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_id);
    ErrorTracker::trackFrom("Framebuffer renderbuffer attach (after bind)");
    gl::FramebufferRenderbuffer(gl::DRAW_FRAMEBUFFER, convert(where),
        gl::RENDERBUFFER, rbuffer->id());
    ErrorTracker::trackFrom(
        "Framebuffer renderbuffer attach (after renderbuffer)");
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, 0);
    ErrorTracker::trackFrom("Framebuffer renderbuffer attach (after clear)");
}

boost::shared_ptr<Texture> Framebuffer::getTextureAttachment(
    Attachment where) {

    return m_textures[where].second;
}

bool Framebuffer::isTexture(Attachment where) {
    return m_textures[where].first;
}

bool Framebuffer::isRenderBuffer(Attachment where) {
    return m_rbuffers[where].first;
}

bool Framebuffer::isAttached(Attachment where) {
    return m_textures[where].first || m_rbuffers[where].first;
}

void Framebuffer::bindRead() {
    ErrorTracker::trackFrom("Framebuffer read bind (before all)");
    gl::BindFramebuffer(gl::READ_FRAMEBUFFER, m_id);
    ErrorTracker::trackFrom("Framebuffer read bind (after bind)");
}

void Framebuffer::bindWrite() {
    ErrorTracker::trackFrom("Framebuffer write bind (before all)");
    gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, m_id);
    ErrorTracker::trackFrom("Framebuffer write bind (after bind)");

    // check if it's complete
    auto result = gl::CheckFramebufferStatus(gl::DRAW_FRAMEBUFFER);
    if(result != gl::FRAMEBUFFER_COMPLETE) {
        Message3(Render, Error,
            "Trying to use incomplete Framebuffer for writing: " << result);
    }
    ErrorTracker::trackFrom("Framebuffer write bind (after complete check)");

    // determine what we want to render into
    GLenum buffers[4];
    for(int i = 0; i < 4; i ++) {
        if(isAttached(Attachment(ColourBuffer0 + i)))
            buffers[i] = gl::COLOR_ATTACHMENT0 + (i);
        else buffers[i] = gl::NONE;
    }
    gl::DrawBuffers(4, buffers);
    ErrorTracker::trackFrom("Framebuffer write bind (after glDrawBuffers)");
}

GLenum Framebuffer::convert(Attachment where) {
    switch(where) {
    case DepthBuffer:
        return gl::DEPTH_ATTACHMENT;
    case ColourBuffer0:
        return gl::COLOR_ATTACHMENT0;
    case ColourBuffer1:
        return gl::COLOR_ATTACHMENT1;
    case ColourBuffer2:
        return gl::COLOR_ATTACHMENT2;
    case ColourBuffer3:
        return gl::COLOR_ATTACHMENT3;
    default:
        Message3(Render, Fatal,
            "Unknown Framebuffer::Attachment passed to convert.");
        break;
    }

    // make GCC quiet, even though the default branch abort()s.
    return gl::INVALID_VALUE;
}

}  // namespace Render
}  // namespace Kriti
