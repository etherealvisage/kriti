#ifndef KRITI_INTERFACE__MOUSE_ROUTER_H
#define KRITI_INTERFACE__MOUSE_ROUTER_H

#include "event/EventRouter.h"

namespace Kriti {
namespace Interface {

class MouseRouter : public Event::EventRouter {
public:
    enum ButtonSignalName {
        LeftButton,
        MiddleButton,
        RightButton,
        ButtonSignalNames
    };
private:
    boost::signals2::signal<void (int, int)> m_motionSignal;
    boost::signals2::signal<void (bool)> m_buttonSignals[ButtonSignalNames];
public:
    boost::signals2::signal<void (int, int)> &motionSignal() {
        return m_motionSignal;
    }

    boost::signals2::signal<void (bool)> &buttonSignal(
        ButtonSignalName signal) {

        return m_buttonSignals[signal];
    }
};

}  // namespace Interface
}  // namespace Kriti

#endif
