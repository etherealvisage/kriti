#include "Layout.h"

namespace Kriti {
namespace GUI {

void Layout::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    for(auto child : m_items) {
        child->fill(container);
    }
}

}  // namespace GUI
}  // namespace Kriti
