#ifndef KRITI_EVENT__EVENT_ROUTER_H
#define KRITI_EVENT__EVENT_ROUTER_H

#include <boost/signal.hpp>

namespace Kriti {
namespace Event {

class EventRouter {
public:
    void fire(boost::signal<void ()> &signal) {
        signal();
    }

    template<typename T1>
    void fire(boost::signal<void (T1)> &signal, T1 t1) {
        signal(t1);
    }

    template<typename T1, typename T2>
    void fire(boost::signal<void (T1, T2)> &signal, T1 t1, T2 t2) {
        signal(t1, t2);
    }

    template<typename T1, typename T2, typename T3>
    void fire(boost::signal<void (T1, T2, T3)> &signal, T1 t1, T2 t2, T3 t3) {
        signal(t1, t2, t3);
    }

    boost::signal<void ()> simpleListener;
    boost::signal<void (int)> exampleListener;
};

}  // namespace Event
}  // namespace Kriti

#endif
