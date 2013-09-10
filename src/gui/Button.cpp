#include <boost/make_shared.hpp>

#include "Button.h"
#include "Scale.h"

#include "render/RenderableFactory.h"
#include "render/Stage.h"

#include "MessageSystem.h"

namespace Kriti {
namespace GUI {

Button::Button(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font> font, std::string text) : Widget(stretch),
    m_minSize(minSize), m_activation(0.0) { 
    
    m_label = boost::make_shared<Label>(stretch, font, text);
}

Math::Vector Button::minSize() {
    return m_minSize;
}

void Button::updated(boost::shared_ptr<OutlineRegistry> registry) {
    registry->updateOutline(shared_from_this(), pos(), size());

#if 0
    // TODO: re-use old renderable . . . this is expensive.
    if(m_renderable) m_stage->removeRenderable(m_renderable);
    m_renderable = Render::RenderableFactory().fromQuad(
        pos(),
        pos() + Math::Vector(0,size().y()),
        pos() + size(),
        pos() + Math::Vector(size().x()),
        "gui_button");
    m_renderable->renderSequence(0)->extraParams().setParam("button_xscale",
        (size().x() / Scale().xtotal()) / scale().x());
    m_renderable->renderSequence(0)->extraParams().setParam("button_yscale",
        (size().y() / Scale().ytotal()) / scale().y());

    if(mouseState().posSet()) {
        m_activation = std::pow(0.3, m_activation)/2.0;
        m_renderable->renderSequence(0)->extraParams().setParam(
            "button_click", mouseState().button(0)?1.0:0.0);
        
        if(mouseState().button(0)) {
            m_wasClicked = true;
        }
        else if(!mouseState().button(0) && m_wasClicked) {
            Message3(GUI, Debug, "Button click!");
            m_wasClicked = false;
        }
    }
    else {
        m_activation *= 0.5;
        m_renderable->renderSequence(0)->extraParams().setParam(
            "button_click", 0.0);
        m_wasClicked = false;
    }

    m_renderable->renderSequence(0)->extraParams().setParam(
        "button_activation", m_activation);


    m_stage->addRenderable(m_renderable);

    m_label->update(registry,
        pos() + Scale().padding()*scale() + Scale().perLayer(),
        size() - Scale().padding()*scale()*2, scale());
#endif
}

}  // namespace GUI
}  // namespace Kriti
