#include "LayoutItem.h"

#include "Style.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"

namespace Kriti {
namespace GUI {

LayoutItem::LayoutItem() {
    m_style = ResourceRegistry::get<Style>("default");
}

void LayoutItem::update(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector pos, Math::Vector size, Math::Vector scale,
    Math::Vector clipStart, Math::Vector clipEnd) {

    m_pos = pos, m_size = size, m_scale = scale;
    updated(registry, clipStart, clipEnd);
}

}  // namespace GUI
}  // namespace Kriti
