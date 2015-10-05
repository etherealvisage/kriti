#ifndef KRITI_GUI__SCROLL_AREA_H
#define KRITI_GUI__SCROLL_AREA_H

#include <boost/shared_ptr.hpp>

#include "LayoutItem.h"
#include "Widget.h"

namespace Kriti {
namespace GUI {

class ScrollArea : public LayoutItem {
private:
    Math::Vector m_minSize, m_stretch;
    boost::shared_ptr<LayoutItem> m_wrapped;
    Math::Vector m_scrollOffset, m_scrollSize;
public:
    ScrollArea(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<LayoutItem> wrapped, Math::Vector scrollSize)
        : m_minSize(minSize), m_stretch(stretch), m_wrapped(wrapped),
        m_scrollSize(scrollSize) {}

    boost::shared_ptr<LayoutItem> wrapped() const { return m_wrapped; }

    virtual Math::Vector minSize() { return m_minSize; }
    virtual Math::Vector stretch() { return m_stretch; }

    Math::Vector &scrollOffset() { return m_scrollOffset; }
    Math::Vector &scrollSize() { return m_scrollSize; }

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
    virtual void flush(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);
};

}  // namespace GUI
}  // namespace Kriti

#endif
