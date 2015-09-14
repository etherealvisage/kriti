#ifndef KRITI_GUI__WIDGET_H
#define KRITI_GUI__WIDGET_H

#include "LayoutItem.h"

#include "../render/Renderable.h"
#include "../render/RenderableContainer.h"

namespace Kriti {

namespace Render {
class Stage;
} // namespace Render

namespace GUI {

class Widget : public LayoutItem {
private:
    Math::Vector m_stretch;
protected:
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    Widget(Math::Vector stretch) : m_stretch(stretch) {}

    virtual Math::Vector stretch() { return m_stretch; }

    boost::shared_ptr<Render::Renderable> renderable() const
        { return m_renderable; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
