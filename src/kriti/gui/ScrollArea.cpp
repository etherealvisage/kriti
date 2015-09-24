#include "ScrollArea.h"

#include "../math/Geometry.h"

namespace Kriti {
namespace GUI {

void ScrollArea::fill(boost::shared_ptr<Render::RenderableContainer>
    container) {
    
    if(m_wrapped) m_wrapped->fill(container);
}

void ScrollArea::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Geometry::intersectAARects(clipStart, clipEnd,
        pos(), pos() + size());

    if(m_wrapped) m_wrapped->update(registry, pos() + m_scrollOffset,
        m_scrollSize, scale(), clipStart, clipEnd);
}

}  // namespace GUI
}  // namespace Kriti
