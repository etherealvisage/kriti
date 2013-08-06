#include <GL/glew.h>

#include <boost/make_shared.hpp>

#include "Stage.h"
#include "TechniqueParams.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Stage::Stage() {
    m_framebuffer = boost::make_shared<Framebuffer>();
    /*m_colourOutput =
        boost::make_shared<Renderbuffer>(Renderbuffer::Colour, 1024, 768);*/
    m_colourOutput =
        boost::make_shared<Texture>(Texture::Colour, 1024, 768);
    m_depthOutput =
        boost::make_shared<Renderbuffer>(Renderbuffer::Depth, 1024, 768);

    m_framebuffer->attach(Framebuffer::ColourBuffer0, m_colourOutput);
    m_framebuffer->attach(Framebuffer::DepthBuffer, m_depthOutput);
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
        texture->bindToUnit(1);
        tp.addParam(std::get<2>(mapping), 1);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto renderable : m_objects) {
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
        renderable->draw(tp);
    }
}

}  // namespace Render
}  // namespace Kriti
