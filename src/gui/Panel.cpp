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

void Panel::updated() {
    // TODO: re-use old renderable . . . this is expensive.
    if(m_renderable) m_stage->removeRenderable(m_renderable);
    m_renderable = Render::RenderableFactory().fromQuad(
        pos(),
        pos() + Math::Vector(0,size().y()),
        pos() + size(),
        pos() + Math::Vector(size().x()),
        "gui_panel");
    m_renderable->renderSequence(0)->materialParams().setParam("panel_xscale",
        (size().x() / Scale().xtotal()) / scale().x());
    m_renderable->renderSequence(0)->materialParams().setParam("panel_yscale",
        (size().y() / Scale().ytotal()) / scale().y());
    m_renderable->renderSequence(0)->materialParams().setParam("panel_activation",
        0.0);

    m_stage->addRenderable(m_renderable);

    if(m_layout) m_layout->update(
        pos() + Scale().padding() + Scale().perLayer(),
        size() - Scale().padding()*2, scale());
    
    //m_layout->update(pos() + Scale().perLayer(), size(), scale());
}

}  // namespace GUI
}  // namespace Kriti
