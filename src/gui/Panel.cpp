#include "Panel.h"
#include "Scale.h"
#include "Layout.h"

#include "render/RenderableFactory.h"
#include "render/Stage.h"

#include "MessageSystem.h"

namespace Kriti {
namespace GUI {

Math::Vector Panel::minSize() {
    return m_minSize + Scale().padding()*2;
}

void Panel::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) {
        container->add(m_renderable);
    }
    m_layout->fill(container);
}

void Panel::updated(boost::shared_ptr<OutlineRegistry> registry) {
    registry->updateOutline(shared_from_this(), pos(), size());

    if(!m_renderable) {
        m_renderable = Render::RenderableFactory().fromQuad(
            pos(),
            pos() + Math::Vector(0,size().y()),
            pos() + size(),
            pos() + Math::Vector(size().x()),
            "gui_panel");
    }
    else {
        std::vector<Math::Vector> loc;
        loc.push_back(pos());
        loc.push_back(pos() + Math::Vector(0,size().y()));
        loc.push_back(pos() + size());

        loc.push_back(pos());
        loc.push_back(pos() + size());
        loc.push_back(pos() + Math::Vector(size().x()));

        m_renderable->renderSequence(0)->vao()->vbo(
            Render::VAO::Vertex)->setData3(loc);
    }
    m_renderable->renderSequence(0)->extraParams().setParam("panel_xscale",
        (size().x() / Scale().xtotal()) / scale().x());
    m_renderable->renderSequence(0)->extraParams().setParam("panel_yscale",
        (size().y() / Scale().ytotal()) / scale().y());

    if(mouseState().posSet()) {
        m_activation = std::pow(0.3, m_activation)/2.0;
    }
    else {
        m_activation *= 0.5;
    }

    m_renderable->renderSequence(0)->extraParams().setParam(
        "panel_activation", m_activation);

    if(m_layout) m_layout->update(registry,
        pos() + Scale().padding()*scale() + Scale().perLayer(),
        size() - Scale().padding()*scale()*2, scale());
}

}  // namespace GUI
}  // namespace Kriti
