#include <boost/make_shared.hpp>

#include "Layout.h"
#include "LayoutSpacer.h"

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

void Layout::addSpacer(Math::Vector minSize, Math::Vector stretch) {
    m_items.push_back(boost::make_shared<LayoutSpacer>(minSize, stretch));
}

}  // namespace GUI
}  // namespace Kriti
