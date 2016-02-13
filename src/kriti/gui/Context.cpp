#include <boost/make_shared.hpp>

#include "Context.h"
#include "LayoutItem.h"

#include "../interface/Video.h"
#include "../render/ConstantUniformHook.h"
#include "../render/RenderableContainer.h"
#include "../math/ViewGenerator.h"
#include "../state/Context.h"
#include "../TimeValue.h"

namespace Kriti {
namespace GUI {

Context::Context() {
    m_enabled = false;

    m_outlineRegistry = boost::make_shared<OutlineRegistry>();
    m_mouseInteractor = boost::make_shared<MouseInteractor>();
    m_mouseCursor = boost::make_shared<MouseCursor>();

    auto aratio = Interface::Video::get()->aspectRatio();

    auto camhook = boost::make_shared<Render::ConstantUniformHook>();
    camhook->uniforms().setParam("u_camera",
        Math::ViewGenerator().orthogonal(
            0.0, aratio, 1.0, 0.0,
            -10.0, 10.0));

    m_container = boost::make_shared<Render::RenderableContainer>();
    m_container->addUniformHook(camhook);

    m_container->add(m_mouseCursor->renderable());
}

void Context::hookOnto(boost::shared_ptr<State::Context> context) {
    context->addListener("mouse_moved",
        boost::function<void (double, double)>([this](double x, double y){
            if(!m_enabled) return;
            m_mouseInteractor->updateMouseCoordinates(x, y);
            m_mouseCursor->updateMouseCoordinates(x, y);
        }));
    context->addListener("mouse_down",
        boost::function<void (int)>([this](int b){
            if(!m_enabled) return;
            m_mouseInteractor->updateMouseButton(b, true);
        }));
    context->addListener("mouse_up",
        boost::function<void (int)>([this](int b){
            if(!m_enabled) return;
            m_mouseInteractor->updateMouseButton(b, false);
        }));
    context->addListener("key_down",
        boost::function<void (SDL_Keycode)>([this](SDL_Keycode key){
            if(!m_enabled) return;
            KeyboardFocus::get()->keyPressed(key);
        }));
    context->addListener("key_up",
        boost::function<void (SDL_Keycode)>([this](SDL_Keycode key){
            if(!m_enabled) return;
            KeyboardFocus::get()->keyReleased(key);
        }));
    context->addListener("text_input",
        boost::function<void (std::string)>([this](std::string text){
            if(!m_enabled) return;
            KeyboardFocus::get()->textEntered(text);
        }));
    context->addListener("new_frame",
        boost::function<void (TimeValue)>([this](TimeValue){
            if(!m_enabled) return;

            m_mouseInteractor->updateMouseActivation(m_outlineRegistry);

            update();
        }));
}

void Context::addRootItem(boost::shared_ptr<LayoutItem> item,
    Math::Vector location, Math::Vector size, Math::Vector scale) {

    m_rootItems.push_back(boost::make_tuple(item, location, size, scale));

    item->setContext(shared_from_this());
}

void Context::update() {
    for(auto &root : m_rootItems) {
        auto &item = boost::get<0>(root);
        item->update(m_outlineRegistry, boost::get<1>(root),
            boost::get<2>(root), boost::get<3>(root));
        item->fill(m_container);
    }
}

}  // namespace GUI
}  // namespace Kriti
