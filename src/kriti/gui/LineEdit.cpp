#include <boost/make_shared.hpp>


#include "LineEdit.h"
#include "Scale.h"
#include "Style.h"

#include "../math/Geometry.h"
#include "../render/RenderableFactory.h"

namespace Kriti {
namespace GUI {

LineEdit::LineEdit(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, std::string text)
    : Widget(stretch), m_minSize(minSize) {

    m_focused = false;

    m_label = boost::make_shared<Label>(Math::Vector(), stretch, font, text);
}

Math::Vector LineEdit::minSize() {
    Math::Vector label_min = m_label->minSize() + Scale().padding()*scale()*2;

    return Math::Vector(
        std::max(label_min.x(), m_minSize.x()),
        std::max(label_min.y(), m_minSize.y()));
}

void LineEdit::lostFocus(KeyboardFocus &focus) {
    m_focused = false;
}

void LineEdit::gainedFocus(KeyboardFocus &focus) {
    m_focused = true;
}

void LineEdit::keyPressed(SDL_Keycode key) {
    if(key == SDLK_BACKSPACE) {
        std::string text = m_label->text();
        if(text.length() > 0) {
            text.pop_back();
            m_label->setText(text);
        }
    }
}

void LineEdit::keyReleased(SDL_Keycode key) {
    
}

void LineEdit::textEntered(std::string text) {
    m_label->setText(m_label->text() + text);
}

void LineEdit::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->add(m_renderable);
    if(m_label) m_label->fill(container);
}

void LineEdit::flush(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->remove(m_renderable);
    if(m_label) m_label->flush(container);
}

void LineEdit::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Vector outlineStart = pos(), outlineEnd = pos()+size();
    Math::Geometry::intersectAARects(outlineStart, outlineEnd,
        clipStart, clipEnd);
    if(!Math::Geometry::isAARectEmpty(outlineStart, outlineEnd))
        registry->updateOutline(shared_from_this(), outlineStart,
            outlineEnd-outlineStart);

    if(!m_renderable) {
        m_renderable = Render::RenderableFactory().fromQuad(
            pos(),
            pos() + Math::Vector(0,size().y()),
            pos() + size(),
            pos() + Math::Vector(size().x()),
            "gui_panel");
    }
    else {
        std::vector<Math::Vector> loc;
        loc.push_back(pos());
        loc.push_back(pos() + Math::Vector(0,size().y()));
        loc.push_back(pos() + size());

        loc.push_back(pos());
        loc.push_back(pos() + size());
        loc.push_back(pos() + Math::Vector(size().x()));

        m_renderable->renderSequence(0)->vao()->vbo(
            Render::VAO::Vertex)->setData3(loc);
    }
    m_renderable->renderSequence(0)->extraParams().setParam("gui_xdpi",
        size().x() / Scale().xscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_ydpi",
        size().y() / Scale().yscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_start",
        clipStart);
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_end",
        clipEnd);
    m_renderable->renderSequence(0)->extraParams().add(style()->uniforms());

    #if 0
    // TODO: make this activation not framerate-specific
    if(mouseState().posSet()) {
        m_activation = std::pow(0.3, m_activation)/2.0;
        m_renderable->renderSequence(0)->extraParams().setParam(
            "button_click", mouseState().button(0)?1.0:0.0);
        
        if(mouseState().button(0)) {
            m_wasClicked = true;
        }
        else if(!mouseState().button(0) && m_wasClicked) {
            auto event = m_clickEvent.lock();
            if(event) event->fire(boost::make_tuple());

            m_wasClicked = false;
        }
    }
    else {
        m_activation *= 0.5;
        m_renderable->renderSequence(0)->extraParams().setParam(
            "button_click", 0.0);
        m_wasClicked = false;
    }

    m_renderable->renderSequence(0)->extraParams().setParam(
        "button_activation", m_activation);
    #endif

    m_label->update(registry,
        pos() + Scale().padding()*scale() + Scale().perLayer(),
        size() - Scale().padding()*scale()*2, scale(), clipStart, clipEnd);
}



}  // namespace GUI
}  // namespace Kriti
