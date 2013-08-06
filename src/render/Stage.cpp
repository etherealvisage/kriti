#include <GL/glew.h>

#include <boost/make_shared.hpp>

#include "Stage.h"
#include "TechniqueParams.h"
#include "TextureContext.h"

#include "interface/Video.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Stage::Stage(int outputs, int width, int height) {
    if(width == -1) width = Interface::Video::instance()->width();
    if(height == -1) height = Interface::Video::instance()->height();
    m_width = width, m_height = height;

    m_framebuffer = boost::make_shared<Framebuffer>();

    for(int i = 0; i < outputs; i ++) {
        m_framebuffer->attach(
            Framebuffer::Attachment(Framebuffer::ColourBuffer0 + i),
            boost::make_shared<Texture>(Texture::Colour, m_width,
                m_height));
    }
    m_framebuffer->attach(Framebuffer::DepthBuffer, 
        boost::make_shared<Renderbuffer>(Renderbuffer::Depth, m_width,
            m_height));

    m_textureContext = boost::make_shared<TextureContext>();
}

void Stage::addMapping(int previousIndex, Framebuffer::Attachment attachment,
    std::string uniformName) {

    auto prev = m_previous[previousIndex];
    auto pfb = prev->framebuffer();

    m_attachments.push_back(std::make_tuple(prev, attachment, uniformName));
}

void Stage::addRenderable(boost::shared_ptr<Renderable> renderable) {
    m_objects.push_back(renderable);
}

void Stage::removeRenderable(boost::shared_ptr<Renderable> renderable) {
    for(unsigned i = 0; i < m_objects.size(); i ++) {
        if(m_objects[i] == renderable) {
            m_objects[i] = m_objects.back();
            m_objects.pop_back();
            return;
        }
    }
}

void Stage::render(bool isLast) {
    auto cameraMatrix = m_camera.matrix();

    if(!isLast) m_framebuffer->bindWrite();
    else {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glDrawBuffer(GL_BACK);
    }

    TechniqueParams tp;

    tp.addParam("camera", cameraMatrix);
    
    // HACK: use texture unit 1 for everything...
    for(auto mapping : m_attachments) {
        auto fb = std::get<0>(mapping)->framebuffer();
        auto texture = fb->getTextureAttachment(std::get<1>(mapping));
        tp.addParam(std::get<2>(mapping), texture);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto renderable : m_objects) {
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
        renderable->draw(tp, m_textureContext);
    }
    m_textureContext->clearBindings();
}

}  // namespace Render
}  // namespace Kriti
