#ifndef KRITI_STATE__DELAY_PROXY_H
#define KRITI_STATE__DELAY_PROXY_H

#include <algorithm>
#include <queue>

#include <boost/shared_ptr.hpp>

#include "Context.h"

#include "../TimeValue.h"

namespace Kriti {
namespace State {

class DelayProxy {
private:
    static boost::shared_ptr<DelayProxy> s_singleton;
public:
    static boost::shared_ptr<DelayProxy> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<DelayProxy>(new DelayProxy());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
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
private:
    DelayProxy() {}
public:
    void fire(TimeValue rel, boost::weak_ptr<Context::Event> event,
        boost::any params) {

        auto e = event.lock();
        if(!e) return;

        auto f = boost::bind(&Context::Event::fire, e.get(), params, false);
        m_events.push(Event{rel + TimeValue::current(), f});
    }

    void processQueued();
};

}  // namespace State
}  // namespace Kriti

#endif
