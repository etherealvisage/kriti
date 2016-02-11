#include <boost/make_shared.hpp>


#include "LineEdit.h"
#include "Scale.h"
#include "Style.h"
#include "PackedLayout.h"
#include "KeyboardFocus.h"
#include "Context.h"

#include "../math/Geometry.h"
#include "../render/RenderableFactory.h"

namespace Kriti {
namespace GUI {

LineEdit::LineEdit(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, std::string text)
    : Widget(stretch), m_minSize(minSize) {

    createEventContext();

    m_focused = false;

    m_panel = boost::make_shared<Panel>(minSize, stretch,
        boost::make_shared<PackedLayout>(Math::Vector(1,1),
            PackedLayout::Vertical));
    m_label = boost::make_shared<Label>(Math::Vector(), Math::Vector(1,1),
        font, text);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));
    m_panel->layout()->addItem(m_label);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));

    /* grab focus when left-clicked */
    eventContext()->addListener("mouseClicked",
        boost::function<void (int)>([this](int button){
            // only interested in left-clicks
            if(button != 0) return;
            KeyboardFocus::get()->changeFocus(this->targetPointer());
        }));
}

Math::Vector LineEdit::minSize() {
    return m_panel->minSize();
}

void LineEdit::lostFocus() {
    m_focused = false;
    eventContext()->fire("lostFocus", boost::make_tuple(), true);
}

void LineEdit::gainedFocus() {
    m_focused = true;
    eventContext()->fire("gainedFocus", boost::make_tuple(), true);
}

void LineEdit::keyPressed(SDL_Keycode key) {
    if(key == SDLK_BACKSPACE) {
        std::string text = m_label->text();
        if(text.length() > 0) {
            text.pop_back();
            m_label->setText(text);
            eventContext()->fire("textChanged", boost::make_tuple(), true);
        }
    }
    else if(key == SDLK_RETURN) {
        KeyboardFocus::get()->clearFocus();
    }
}

void LineEdit::keyReleased(SDL_Keycode key) {
    
}

void LineEdit::textEntered(std::string text) {
    m_label->setText(m_label->text() + text);
    eventContext()->fire("textChanged", boost::make_tuple(), true);
}

void LineEdit::requestFocus() {
    KeyboardFocus::get()->changeFocus(targetPointer());
}

boost::shared_ptr<LineEdit> LineEdit::targetPointer() {
    auto st = this->shared_from_this();
    return boost::reinterpret_pointer_cast<LineEdit>(st);
}

std::string LineEdit::text() const {
    return m_label->text();
}

void LineEdit::setText(std::string text) {
    m_label->setText(text);
}

void LineEdit::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    m_panel->fill(container);
}

void LineEdit::flush(
    boost::shared_ptr<Render::RenderableContainer> container) {

    m_panel->flush(container);
}

void LineEdit::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Vector outlineStart, outlineEnd;
    standardOutlineUpdate(registry, clipStart, clipEnd, outlineStart,
        outlineEnd);

    // Children shouldn't respond to mouseovers, so no registry.
    m_panel->update(nullptr, pos(), size(), scale(), outlineStart, outlineEnd);
}

}  // namespace GUI
}  // namespace Kriti
