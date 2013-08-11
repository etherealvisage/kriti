#ifndef KRITI_GUI__MOUSE_INTERACTOR_H
#define KRITI_GUI__MOUSE_INTERACTOR_H

#include "OutlineRegistry.h"

namespace Kriti {
namespace GUI {

class MouseInteractor {
private:
    int m_mouseX, m_mouseY, m_buttons;
    boost::weak_ptr<LayoutItem> m_lastHover;
public:
    MouseInteractor() : m_buttons(0) {}

    void updateMouseCoordinates(int x, int y);
    void updateMouseButton(int which, bool value);

    void updateMouseActivation(boost::shared_ptr<OutlineRegistry> registry);
};

}  // namespace GUI
}  // namespace Kriti

#endif
