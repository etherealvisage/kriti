#include <boost/make_shared.hpp>


#include "LineEdit.h"
#include "Scale.h"
#include "Style.h"
#include "PackedLayout.h"

#include "../math/Geometry.h"
#include "../render/RenderableFactory.h"

namespace Kriti {
namespace GUI {

LineEdit::LineEdit(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, std::string text)
    : Widget(stretch), m_minSize(minSize) {

    m_focused = false;

    m_panel = boost::make_shared<Panel>(minSize, stretch,
        boost::make_shared<PackedLayout>(Math::Vector(1,1),
            PackedLayout::Vertical));
    m_label = boost::make_shared<Label>(Math::Vector(), Math::Vector(1,1),
        font, text);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));
    m_panel->layout()->addItem(m_label);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));
}

Math::Vector LineEdit::minSize() {
    return m_panel->minSize();
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
    m_panel->fill(container);
}

void LineEdit::flush(
    boost::shared_ptr<Render::RenderableContainer> container) {

    m_panel->flush(container);
}

void LineEdit::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    // Children shouldn't respond to mouseovers, so no registry.
    m_panel->update(nullptr, pos(), size(), scale(), clipStart, clipEnd);
}

}  // namespace GUI
}  // namespace Kriti
