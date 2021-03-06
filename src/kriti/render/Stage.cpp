#include <cstring>
#include <algorithm>

#include "../ogl.h"

#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include "Stage.h"
#include "Uniforms.h"
#include "TextureContext.h"
#include "ErrorTracker.h"

#include "../interface/Video.h"

#include "../profile/Tracker.h"

#include "../math/ViewGenerator.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"
#include "../XMLResource.h"

namespace Kriti {
namespace Render {

Stage::Stage() {}

Stage::Stage(int outputs, int width, int height, std::string name)
    : m_name(name) {
    
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
    for(auto &child : node.children()) {
        if(std::strcmp(child.name(), "previous")) continue;

        std::string pname = child.text().as_string("");
        auto prev = ResourceRegistry::get<Stage>(pname);
        if(!prev) {
            Message3(Render, Error, "Couldn't find previous stage " << pname);
            continue;
        }

        addPrevious(prev);
    }

    for(auto &child : node.children()) {
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
        const std::map<std::string, Framebuffer::Attachment> whichMap = {
            {"colour0", Framebuffer::ColourBuffer0},
            {"colour1", Framebuffer::ColourBuffer1},
            {"colour2", Framebuffer::ColourBuffer2},
            {"colour3", Framebuffer::ColourBuffer3},
            {"depth", Framebuffer::DepthBuffer}
        };
        if(whichMap.count(whichString) == 0) {
            Message3(Render, Warning, "Unknown attachment: " << whichString);
            continue;
        }

        std::string materialString = child.attribute("material").as_string();
        std::string uniform = child.attribute("to").as_string();

        auto mat = ResourceRegistry::get<Render::Material>(materialString);
        addMapping(from, whichMap.at(whichString), mat, uniform);
    }

    return true;
}

void Stage::addMapping(int previousIndex, Framebuffer::Attachment attachment,
    boost::shared_ptr<Render::Material> material, std::string uniformName) {

    auto prev = m_previous[previousIndex];
    addMapping(prev, attachment, material, uniformName);
}

void Stage::addMapping(boost::shared_ptr<Stage> prev,
    Framebuffer::Attachment attachment,
    boost::shared_ptr<Render::Material> material, std::string uniformName) {

    auto pfb = prev->framebuffer();

    m_attachments.push_back(std::make_tuple(prev, attachment, material,
        uniformName));
}

void Stage::render(Uniforms &globalParams, bool isLast) {
    Profile::Tracker::get()->beginGLTimer(m_name);

    if(!isLast) m_framebuffer->bindWrite();
    else {
        gl::BindFramebuffer(gl::DRAW_FRAMEBUFFER, 0);
        gl::DrawBuffer(gl::BACK);
    }

    MaterialParams materialParams;

    for(auto &mapping : m_attachments) {
        auto fb = std::get<0>(mapping)->framebuffer();
        auto texture = fb->getTextureAttachment(std::get<1>(mapping));

        auto material = std::get<2>(mapping);
        materialParams[material].setParam(std::get<3>(mapping), texture);
    }

    gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

    m_renderables->draw(globalParams, materialParams);

    Profile::Tracker::get()->endGLTimer(m_name);
}

void Stage::initialize(int outputs, int width, int height) {
    if(width == -1) width = Interface::Video::get()->width();
    if(height == -1) height = Interface::Video::get()->height();
    m_width = width, m_height = height;

    m_framebuffer = boost::make_shared<Framebuffer>();

    for(int i = 0; i < outputs; i ++) {
        boost::shared_ptr<Texture> texture;
        if(Interface::Video::get()->msaa()) {
            texture = boost::make_shared<Texture>(Texture::Colour,
                Texture::Simple, m_width, m_height,
                Interface::Video::get()->aasamples());
        }
        else {
            texture = boost::make_shared<Texture>(Texture::Colour,
                Texture::Simple, m_width, m_height);
        }
        m_framebuffer->attach(
            Framebuffer::Attachment(Framebuffer::ColourBuffer0 + i), texture);
    }
    boost::shared_ptr<Renderbuffer> renderbuffer;
    if(Interface::Video::get()->msaa()) {
        renderbuffer = boost::make_shared<Renderbuffer>(Renderbuffer::Depth,
            m_width, m_height, Interface::Video::get()->aasamples());
    }
    else {
        renderbuffer = boost::make_shared<Renderbuffer>(Renderbuffer::Depth,
            m_width, m_height);
    }
    m_framebuffer->attach(Framebuffer::DepthBuffer, renderbuffer);

    Profile::Tracker::get()->addGLTimer(m_name);

    m_renderables = boost::make_shared<RenderableContainer>();
}

void Stage::renderRenderable(Uniforms &globalParams,
    MaterialParams &materialParams, boost::shared_ptr<Renderable> renderable) {

    ErrorTracker::trackFrom("Before renderable drawing");
    renderable->draw(globalParams, materialParams);
    ErrorTracker::trackFrom("After renderable drawing");
}

}  // namespace Render
}  // namespace Kriti
