#include <boost/make_shared.hpp>

#include "Layout.h"
#include "LayoutSpacer.h"
#include "Context.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

Layout::~Layout() {
    clearItems();
}

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

void Layout::addItem(boost::shared_ptr<LayoutItem> item) {
    m_items.push_back(item);
    reparent(item);
}

void Layout::addSpacer(Math::Vector minSize, Math::Vector stretch) {
    m_items.push_back(boost::make_shared<LayoutSpacer>(minSize, stretch));
    reparent(m_items.back());
}

void Layout::clearItems() {
    // find context
    auto c = findGuiContext().lock();
    if(c) {
        for(auto &item : m_items) {
            item->flush(c->container());
            unparent(item);
        }
    }
    m_items.clear();
}

}  // namespace GUI
}  // namespace Kriti
