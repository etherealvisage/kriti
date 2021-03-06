#ifndef KRITI_RENDER__FRAMEBUFFER_H
#define KRITI_RENDER__FRAMEBUFFER_H

#include <utility>

#include <boost/shared_ptr.hpp>

#include "Texture.h"
#include "Renderbuffer.h"

namespace Kriti {
namespace Render {

class Framebuffer {
public:
    enum Attachment {
        DepthBuffer,
        // the following need to be contiguously numbered
        ColourBuffer0,
        ColourBuffer1,
        ColourBuffer2,
        ColourBuffer3,
        Attachments
    };
private:
    GLuint m_id;
    std::pair<bool, boost::shared_ptr<Texture>> m_textures[Attachments];
    std::pair<bool, boost::shared_ptr<Renderbuffer>> m_rbuffers[Attachments];
public:
    Framebuffer();
    ~Framebuffer();

    void attach(Attachment where, boost::shared_ptr<Texture> texture); 
    void attach(Attachment where, boost::shared_ptr<Renderbuffer> rbuffer); 

    boost::shared_ptr<Texture> getTextureAttachment(Attachment where);

    bool isTexture(Attachment where);
    bool isRenderBuffer(Attachment where);
    bool isAttached(Attachment where);

    void bindRead();
    void bindWrite();
private:
    GLenum convert(Attachment where);
};

}  // namespace Render
}  // namespace Kriti

#endif
