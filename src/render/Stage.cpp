#include <GL/glew.h>

#include <boost/make_shared.hpp>

#include "Stage.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

Stage::Stage() {
    {
        Message3(Render, Debug, "Checking OpenGL error state before FBO creation...");
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
    }
    m_framebuffer = boost::make_shared<Framebuffer>();
    {
        Message3(Render, Debug, "Checking OpenGL error state after FBO creation...");
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
    }
    m_colourOutput =
        boost::make_shared<Renderbuffer>(Renderbuffer::Colour, 1024, 768);
    {
        Message3(Render, Debug, "Checking OpenGL error state after Colour RB creation...");
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
    }
    m_depthOutput =
        boost::make_shared<Renderbuffer>(Renderbuffer::Depth, 1024, 768);
    {
        Message3(Render, Debug, "Checking OpenGL error state after Depth RB creation...");
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
    }

    m_framebuffer->attach(Framebuffer::ColourBuffer0, m_colourOutput);
    m_framebuffer->attach(Framebuffer::DepthBuffer, m_depthOutput);

    {
        Message3(Render, Debug, "Checking OpenGL error state after attachment");
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
    }
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

    for(auto renderable : m_objects) {
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
        renderable->draw(cameraMatrix);
    }
}

}  // namespace Render
}  // namespace Kriti
