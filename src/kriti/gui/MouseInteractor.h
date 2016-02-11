#ifndef KRITI_GUI__MOUSE_INTERACTOR_H
#define KRITI_GUI__MOUSE_INTERACTOR_H

#include "OutlineRegistry.h"

namespace Kriti {
namespace GUI {

class MouseInteractor {
private:
    double m_mouseX, m_mouseY;
    int m_buttons;
    boost::weak_ptr<LayoutItem> m_lastHover;
    bool m_lastClicked;
public:
    MouseInteractor() : m_mouseX(0), m_mouseY(0), m_buttons(0),
        m_lastClicked(false) {}

    void updateMouseCoordinates(double x, double y);
    void updateMouseButton(int which, bool value);

    void updateMouseActivation(boost::shared_ptr<OutlineRegistry> registry);
};

}  // namespace GUI
}  // namespace Kriti

#endif
