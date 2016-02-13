#ifndef KRITI_GUI__PANEL_H
#define KRITI_GUI__PANEL_H

#include <boost/shared_ptr.hpp>

#include "Widget.h"
#include "Layout.h"

#include "../render/Renderable.h"

namespace Kriti {
namespace GUI {

class Layout;

class Panel : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Layout> m_layout;
    bool m_parity;
public:
    Panel(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Layout> layout, bool parity = false)
        : Widget(stretch), m_minSize(minSize), m_layout(layout),
            m_parity(parity) { createEventContext(); reparent(m_layout); }
    ~Panel() { unparent(m_layout); }

    boost::shared_ptr<Layout> layout() const { return m_layout; }

    virtual Math::Vector minSize();

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
