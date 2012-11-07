#ifndef KRITI_EVENT__EVENT_ROUTER_H
#define KRITI_EVENT__EVENT_ROUTER_H

#include <boost/signal.hpp>

namespace Kriti {
namespace Event {

class EventRouter {
public:
    boost::signal<void ()> simpleListener;
    boost::signal<void (int)> exampleListener;
};

}  // namespace Event
}  // namespace Kriti

#endif
