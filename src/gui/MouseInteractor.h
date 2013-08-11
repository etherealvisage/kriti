#ifndef KRITI_GUI__MOUSE_INTERACTOR_H
#define KRITI_GUI__MOUSE_INTERACTOR_H

#include "OutlineRegistry.h"

namespace Kriti {
namespace GUI {

class MouseInteractor {
private:
    int m_mouseX, m_mouseY;
    boost::weak_ptr<LayoutItem> m_lastHover;
public:
    void updateMouseCoordinates(int x, int y);

    void updateMouseActivation(boost::shared_ptr<OutlineRegistry> registry);
};

}  // namespace GUI
}  // namespace Kriti

#endif
