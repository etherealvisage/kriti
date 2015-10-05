#include "Layout.h"

namespace Kriti {
namespace GUI {

void Layout::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    for(auto child : m_items) {
        child->fill(container);
    }
}

void Layout::flush(boost::shared_ptr<Render::RenderableContainer> container) {
    for(auto child : m_items) {
        child->flush(container);
    }
}

}  // namespace GUI
}  // namespace Kriti
