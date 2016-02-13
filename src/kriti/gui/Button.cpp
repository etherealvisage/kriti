#include <boost/make_shared.hpp>

#include "Button.h"
#include "Scale.h"
#include "Style.h"
#include "Panel.h"
#include "PackedLayout.h"
#include "LayoutSpacer.h"

#include "../render/RenderableFactory.h"

#include "../math/Geometry.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

Button::Button(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, std::string text)
    : Widget(stretch), m_minSize(minSize) {

    createEventContext();

    m_panel = boost::make_shared<Panel>(minSize, stretch,
        boost::make_shared<PackedLayout>(Math::Vector(1,1),
            PackedLayout::Vertical));
    reparent(m_panel);

    m_label = boost::make_shared<Label>(Math::Vector(), Math::Vector(1,1),
        font, text);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));
    m_panel->layout()->addItem(m_label);
    m_panel->layout()->addSpacer(Math::Vector(), Math::Vector(1,1));
}

Button::~Button() {
    unparent(m_panel);
}

Math::Vector Button::minSize() {
    return m_panel->minSize();
}

void Button::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    m_panel->fill(container);
}

void Button::flush(boost::shared_ptr<Render::RenderableContainer> container) {
    m_panel->flush(container);
}

void Button::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Vector outlineStart, outlineEnd;
    standardOutlineUpdate(registry, clipStart, clipEnd, outlineStart,
        outlineEnd);

    // Children shouldn't respond to mouseovers, so no registry.
    m_panel->update(nullptr, pos(), size(), scale(), outlineStart, outlineEnd);
}

}  // namespace GUI
}  // namespace Kriti
