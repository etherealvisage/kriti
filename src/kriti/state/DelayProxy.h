#ifndef KRITI_STATE__DELAY_PROXY_H
#define KRITI_STATE__DELAY_PROXY_H

#include <algorithm>
#include <queue>

#include <boost/shared_ptr.hpp>

#include "Context.h"

#include "../Singleton.h"
#include "../TimeValue.h"

namespace Kriti {
namespace State {

/* Can be used as a singleton, but individual instances are also kosher. */
class DelayProxy : public Singleton<DelayProxy> {
    friend class Singleton<DelayProxy>;
private:
    struct Event {
        TimeValue time;
        boost::function<void ()> event;

        bool operator<(const Event &other) const { return time < other.time; }
        bool operator>(const Event &other) const { return time > other.time; }
    };
private:
    std::priority_queue<Event, std::vector<Event>,
        std::greater<Event>> m_events;
    TimeValue m_last;
public:
    DelayProxy();
    ~DelayProxy() {}

    void fire(TimeValue rel, boost::weak_ptr<Context::Event> event,
        boost::any params, bool immediate = false) {

        auto e = event.lock();
        if(!e) return;

        auto f = boost::bind(&Context::Event::fire, e.get(), params,
            immediate);
        m_events.push(Event{rel + m_last, f});
    }

    void processQueued(TimeValue time = TimeValue());
};

}  // namespace State
}  // namespace Kriti

#endif
