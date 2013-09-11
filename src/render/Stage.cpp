#include <cstring>
#include <algorithm>

#include <GL/glew.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include "Stage.h"
#include "Uniforms.h"
#include "TextureContext.h"

#include "interface/Video.h"

#include "profile/Tracker.h"

#include "math/ViewGenerator.h"

// HACK: shouldn't have this dependency on the GUI module...
#include "gui/Scale.h"

#include "MessageSystem.h"
#include "ResourceRegistry.h"
#include "XMLResource.h"

namespace Kriti {
namespace Render {

Stage::Stage() {}

Stage::Stage(int outputs, int width, int height, std::string name)
    : m_name(name) {
    
    Message3(Render, Debug, "Making new Stage (!)");

    initialize(outputs, width, height);
}

bool Stage::loadFrom(std::string identifier) {
    auto node = ResourceRegistry::get<XMLResource>(
            "data"
        )->doc().first_element_by_path(
            "/kriti/render/"
        ).find_child_by_attribute(
            "stage", "name", identifier.c_str());

    if(!node) return false;

    m_name = identifier;

    int outputs = node.child("outputs").text().as_int(1);
    int width = -1, height = -1;
    // TODO: support loading width/height from XML resource

    initialize(outputs, width, height);

    // add previous
    for(auto child : node.children()) {
        if(std::strcmp(child.name(), "previous")) continue;

        std::string pname = child.text().as_string("");
        auto prev = ResourceRegistry::get<Stage>(pname);
        if(!prev) {
            Message3(Render, Error, "Couldn't find previous stage " << pname);
            continue;
        }

        addPrevious(prev);
    }

    for(auto child : node.children()) {
        if(std::strcmp(child.name(), "map")) continue;

        std::string fromString = child.attribute("from").as_string();
        int from = 0;
        for(; from < m_previous.size(); from ++)
            if(m_previous[from]->name() == fromString) break;
        if(from == m_previous.size()) {
            Message3(Render, Error, "No previous stage " << fromString);
            continue;
        }

        std::string whichString = child.attribute("which").as_string();
        Framebuffer::Attachment which;
        if(whichString == "colour0") which = Framebuffer::ColourBuffer0;
        else if(whichString == "colour1") which = Framebuffer::ColourBuffer1;
        else if(whichString == "colour2") which = Framebuffer::ColourBuffer2;
        else if(whichString == "colour3") which = Framebuffer::ColourBuffer3;
        else if(whichString == "depth") which = Framebuffer::DepthBuffer;
        else {
            Message3(Render, Debug, "Unknown attachment: " << whichString);
            continue;
        }
        //std::string materialString = child.attribute("material").as_string();
        std::string uniform = child.attribute("to").as_string();

        addMapping(from, which, uniform);
    }

    // HACK: shouldn't have this dependency on the GUI module...
    auto projection = node.child("projection");
    if(projection) {
        std::string type = projection.text().as_string("");

        if(type == "gui") {
            m_camera.setProjection(Math::ViewGenerator().orthogonal(
                GUI::Scale().xtotal(), GUI::Scale().ytotal(), 0.1, 1000.0));
        }
        else {
            Message3(Render, Error, "Unknown projection specified");
        }
    }

    return true;
}

void Stage::addMapping(int previousIndex, Framebuffer::Attachment attachment,
    std::string uniformName) {

    auto prev = m_previous[previousIndex];
    auto pfb = prev->framebuffer();

    m_attachments.push_back(std::make_tuple(prev, attachment, uniformName));
}

void Stage::render(Uniforms &globalParams,
    boost::shared_ptr<TextureContext> textureContext, bool isLast) {

    Profile::Tracker::instance()->beginGLTimer(m_name);
    auto cameraMatrix = m_camera.matrix();

    if(!isLast) m_framebuffer->bindWrite();
    else {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glDrawBuffer(GL_BACK);
    }

    globalParams.setParam("camera", cameraMatrix);
    // HACK: use current time, should be set elsewhere?
    
    for(auto mapping : m_attachments) {
        auto fb = std::get<0>(mapping)->framebuffer();
        auto texture = fb->getTextureAttachment(std::get<1>(mapping));
        globalParams.setParam(std::get<2>(mapping), texture);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderables->iterate(
        boost::bind(&Stage::renderRenderable, this, globalParams,
            textureContext, _1));

    Profile::Tracker::instance()->endGLTimer(m_name);
}

void Stage::initialize(int outputs, int width, int height) {
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

    Profile::Tracker::instance()->addGLTimer(m_name);

    m_renderables = boost::make_shared<RenderableContainer>();
}

void Stage::renderRenderable(Uniforms &globalParams,
    boost::shared_ptr<TextureContext> textureContext,
    boost::shared_ptr<Renderable> renderable) {

    auto error = glGetError();
    if(error != GL_NO_ERROR) {
        Message3(Render, Error, "GL error: " << gluErrorString(error));
    }
    renderable->draw(globalParams, textureContext);
}

}  // namespace Render
}  // namespace Kriti
