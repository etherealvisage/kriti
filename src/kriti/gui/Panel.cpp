#include "Panel.h"
#include "Scale.h"
#include "Layout.h"
#include "Style.h"

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

void Panel::flush(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) {
        container->remove(m_renderable);
    }
    m_layout->flush(container);
}

void Panel::updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd) {
    Math::Vector outlineStart = pos(), outlineEnd = pos()+size();
    Math::Geometry::intersectAARects(outlineStart, outlineEnd,
        clipStart, clipEnd);
    if(!Math::Geometry::isAARectEmpty(outlineStart, outlineEnd) && registry)
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
    m_renderable->renderSequence(0)->extraParams().setParam("gui_xdpi",
        size().x() / Scale().xscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_ydpi",
        size().y() / Scale().yscale());
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_start",
        clipStart);
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_end",
        clipEnd);
    m_renderable->renderSequence(0)->extraParams().add(style()->uniforms());
    m_renderable->renderSequence(0)->extraParams().setParam(
        "gui_border_colour",
        Math::Colour(0.3, 0.3, 0.3, 1.0f));
    m_renderable->renderSequence(0)->extraParams().setParam(
        "gui_panel_colour",
        Math::Colour(0.2, 0.2, 0.2, 1.0f));

    if(m_layout) {
        m_layout->update(registry,
            pos() + Scale().padding()*scale() + Scale().perLayer(),
            size() - Scale().padding()*scale()*2, scale(),
            outlineStart, outlineEnd);
    }
}

}  // namespace GUI
}  // namespace Kriti
