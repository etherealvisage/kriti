#include "LayoutItem.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

void LayoutItem::update(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector pos, Math::Vector size, Math::Vector scale,
    Math::Vector clipStart, Math::Vector clipEnd) {

    m_pos = pos, m_size = size, m_scale = scale;
    updated(registry, clipStart, clipEnd);
}

}  // namespace GUI
}  // namespace Kriti
