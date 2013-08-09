#ifndef KRITI_GUI__WIDGET_H
#define KRITI_GUI__WIDGET_H

#include "LayoutItem.h"

#include "render/Renderable.h"

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
    boost::shared_ptr<Render::Stage> m_stage;
public:
    Widget(Math::Vector stretch, boost::shared_ptr<Render::Stage> stage)
        : m_stretch(stretch), m_stage(stage) {}

    virtual Math::Vector stretch() { return m_stretch; }

    boost::shared_ptr<Render::Renderable> renderable() const
        { return m_renderable; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
