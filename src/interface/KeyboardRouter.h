#ifndef KRITI_INTERFACE__KEYBOARD_ROUTER_H
#define KRITI_INTERFACE__KEYBOARD_ROUTER_H

#include "event/EventRouter.h"

namespace Kriti {
namespace Interface {

class KeyboardRouter : public Event::EventRouter {
public:
    enum SignalName {
#define KEYBOARD_SIGNAL(e, s) e,
#include "KeyboardSignals.h"
#undef KEYBOARD_SIGNAL
        SIGNAL_NAMES
    };
private:
    static const char *s_configNames[];
    boost::signal<void (bool)> m_keySignals[SIGNAL_NAMES];
public:
    const char *configName(SignalName signal) const
        { return s_configNames[signal]; }
    boost::signal<void (bool)> &signal(SignalName signal) {
        return m_keySignals[signal];
    }
};

}  // namespace Interface
}  // namespace Kriti

#endif
