#include "MouseInteractor.h"

#include "Scale.h"
#include "MouseState.h"
#include "LayoutItem.h"

#include "../interface/Video.h"

#include "../state/Context.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

void MouseInteractor::updateMouseCoordinates(double x, double y) {
    m_mouseX = x, m_mouseY = y;
}

void MouseInteractor::updateMouseButton(int which, bool value) {
    if(value) m_buttons |= 1<<which;
    else m_buttons &= ~(1<<which);
}

void MouseInteractor::updateMouseActivation(
    boost::shared_ptr<OutlineRegistry> registry) {

    Math::Vector mpos(m_mouseX, m_mouseY);

    auto itemw = registry->topItemAt(mpos);
    auto item = itemw.lock();
    auto last = m_lastHover.lock();

    MouseState ms;
    ms.setPos(mpos); // TODO: make into local coordinates
    ms.setButton(0, m_buttons & 1);
    ms.setButton(1, m_buttons & 2);
    ms.setButton(2, m_buttons & 4);

    // same item?
    if(last && item == last) {
        MouseState lastms = last->mouseState();
        last->updateMouseState(ms);

        auto context = last->eventContext();
        for(int b = 0; b < 3; b ++) {
            if(!lastms.button(b) && ms.button(b) && context) {
                context->fire("mouseButtonDown", boost::make_tuple(b), true);
                m_lastClicked = true;
            }
            else if(lastms.button(b) && !ms.button(b) && context) {
                context->fire("mouseButtonUp", boost::make_tuple(b), true);
                if(m_lastClicked) {
                    context->fire("mouseClicked", boost::make_tuple(b), true);
                    m_lastClicked = false;
                }
            }
        }

        if(context && ms.pos() != lastms.pos()) {
            context->fire("mouseMovedTo", boost::make_tuple(ms.pos()), true);
        }
    }
    // lost focus?
    else if(last) {
        auto context = last->eventContext();
        if(context) context->fire("mouseLeft", boost::make_tuple(), true);

        last->updateMouseState(MouseState());
        m_lastHover.reset();
        m_lastClicked = false;
    }

    // new item?
    if(item) {
        item->updateMouseState(ms);

        auto context = item->eventContext();
        if(context) {
            context->fire("mouseEntered", boost::make_tuple(), true);
            context->fire("mouseMovedTo", boost::make_tuple(ms.pos()), true);
        }

        m_lastHover = itemw;
    }
}

}  // namespace GUI
}  // namespace Kriti
