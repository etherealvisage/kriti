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
        scale().x() * (size().x() / Scale().xtotal()));
    m_renderable->renderSequence(0)->materialParams().setParam("panel_yscale",
        scale().y() * (size().y() / Scale().ytotal()));

    m_stage->addRenderable(m_renderable);
    
    /*m_layout->update(pos() + Scale().padding() + Scale().perLayer(),
        size() - Scale().padding()*2, scale());*/
}

}  // namespace GUI
}  // namespace Kriti
