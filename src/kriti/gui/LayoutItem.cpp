#include "LayoutItem.h"

#include "Style.h"

#include "../state/Context.h"

#include "../math/Geometry.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"

namespace Kriti {
namespace GUI {

LayoutItem::LayoutItem() {
    m_style = ResourceRegistry::get<Style>("default");
    m_parent = nullptr;
}

void LayoutItem::update(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector pos, Math::Vector size, Math::Vector scale,
    Math::Vector clipStart, Math::Vector clipEnd) {

    m_pos = pos, m_size = size, m_scale = scale;
    updated(registry, clipStart, clipEnd);
}

void LayoutItem::standardOutlineUpdate(
    boost::shared_ptr<OutlineRegistry> registry,
    const Math::Vector &clipStart, const Math::Vector &clipEnd,
    Math::Vector &outlineStart, Math::Vector &outlineEnd) {

    outlineStart = pos(), outlineEnd = pos()+size();
    Math::Geometry::intersectAARects(outlineStart, outlineEnd,
        clipStart, clipEnd);
    if(!Math::Geometry::isAARectEmpty(outlineStart, outlineEnd) && registry)
        registry->updateOutline(shared_from_this(), outlineStart,
            outlineEnd-outlineStart);
}

void LayoutItem::createEventContext() {
    m_context = boost::make_shared<State::Context>();
}

boost::weak_ptr<Context> LayoutItem::findGuiContext() const {
    if(m_guiContext.lock()) return m_guiContext;
    if(m_parent) return m_parent->findGuiContext();
    return boost::weak_ptr<Context>();
}

}  // namespace GUI
}  // namespace Kriti
