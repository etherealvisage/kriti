#include "ItemScaler.h"

namespace Kriti {
namespace GUI {

void ItemScaler::fill(
    boost::shared_ptr<Render::RenderableContainer> container) {
    
    if(m_child) m_child->fill(container);
}

Math::Vector ItemScaler::minSize() {
    if(m_child) return m_child->minSize();
    return Math::Vector();
}

Math::Vector ItemScaler::stretch() {
    if(m_child) return m_child->stretch();
    return Math::Vector();
}

void ItemScaler::updated(boost::shared_ptr<OutlineRegistry> registry) {
    if(!m_child) return;

    if(m_factor > 1.0) {
        // TODO: support superscaling
        return;
    }

    Math::Vector sdiff = size() * (1-m_factor);

    m_child->update(registry, pos()+sdiff/2.0, size() * m_factor,
        scale()*m_factor);
}

}  // namespace GUI
}  // namespace Kriti
