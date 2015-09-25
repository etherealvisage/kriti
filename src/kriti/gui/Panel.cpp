#include "Panel.h"
#include "Scale.h"
#include "Layout.h"

#include "../render/RenderableFactory.h"
#include "../render/Stage.h"

#include "../math/Geometry.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

Math::Vector Panel::minSize() {
    Math::Vector maxmin = m_minSize;
    Math::Vector layoutSize = m_layout->minSize();
    maxmin.setX(std::max(maxmin.x(), layoutSize.x()));
    maxmin.setY(std::max(maxmin.y(), layoutSize.y()));
    return maxmin + Scale().padding()*2;
}

void Panel::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) {
        container->add(m_renderable);
    }
    m_layout->fill(container);
}

void Panel::updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd) {
    Math::Vector outlineStart = pos(), outlineEnd = pos()+size();
    Math::Geometry::intersectAARects(outlineStart, outlineEnd,
        clipStart, clipEnd);
    if(!Math::Geometry::isAARectEmpty(outlineStart, outlineEnd))
        registry->updateOutline(shared_from_this(), outlineStart,
            outlineEnd-outlineStart);

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
    m_renderable->renderSequence(0)->extraParams().setParam("gui_xdpcm",
        size().x() / Scale().xscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_ydpcm",
        size().y() / Scale().yscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_start",
        clipStart);
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_end",
        clipEnd);

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
        size() - Scale().padding()*scale()*2, scale(), clipStart, clipEnd);
}

}  // namespace GUI
}  // namespace Kriti
