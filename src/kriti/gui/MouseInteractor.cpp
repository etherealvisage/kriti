#include "MouseInteractor.h"

#include "Scale.h"
#include "MouseState.h"
#include "LayoutItem.h"

#include "../interface/Video.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

void MouseInteractor::updateMouseCoordinates(int x, int y) {
    m_mouseX = x, m_mouseY = y;
}

void MouseInteractor::updateMouseButton(int which, bool value) {
    if(value) m_buttons |= 1<<which;
    else m_buttons &= ~(1<<which);
}

void MouseInteractor::updateMouseActivation(
    boost::shared_ptr<OutlineRegistry> registry) {

    Math::Vector mpos(
        ((double)m_mouseX / Interface::Video::instance()->width())
            *Scale().xtotal() - Scale().xtotal()/2,
        // invert mouse Y coordinates
        -((double)m_mouseY / Interface::Video::instance()->height())
            *Scale().ytotal() + Scale().ytotal()/2);
    
    auto itemw = registry->topItemAt(mpos);

    auto item = itemw.lock();
    if(item) {
        MouseState ms;
        ms.setPos(mpos); // TODO: make into local coordinates
        ms.setButton(0, m_buttons & 1);
        ms.setButton(1, m_buttons & 2);
        ms.setButton(2, m_buttons & 4);
        item->updateMouseState(ms);
        if(m_lastHover.lock() && item != m_lastHover.lock()) {
            m_lastHover.lock()->updateMouseState(MouseState());
        }
        m_lastHover = itemw;
    }
    else if(m_lastHover.lock()) {
        m_lastHover.lock()->updateMouseState(MouseState());
    }
}

}  // namespace GUI
}  // namespace Kriti
