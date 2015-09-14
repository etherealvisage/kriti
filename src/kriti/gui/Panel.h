#ifndef KRITI_GUI__PANEL_H
#define KRITI_GUI__PANEL_H

#include <boost/shared_ptr.hpp>

#include "Widget.h"

#include "../render/Renderable.h"

namespace Kriti {
namespace GUI {

class Layout;

class Panel : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Layout> m_layout;
    double m_activation;
public:
    Panel(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Layout> layout) : Widget(stretch),
        m_minSize(minSize), m_layout(layout), m_activation(0.0) {}

    boost::shared_ptr<Layout> layout() const { return m_layout; }

    virtual Math::Vector minSize();

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry);
};

}  // namespace GUI
}  // namespace Kriti

#endif
