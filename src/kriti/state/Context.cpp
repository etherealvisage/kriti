#include <iostream> // debugging
#include <algorithm>

#include "Context.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace State {

void Context::Listener::disconnect() {
    auto event = m_event.lock();
    if(!event) return;

    boost::shared_ptr<Listener> self;
    auto &l = event->m_listeners;
    for(int i = 0; i < (int)l.size() && l.size(); i ++) {
        if(l[i].get() == this) {
            self = l[i];
            std::swap(l[i], l.back());
            l.pop_back();
            i --;
        }
    }

    // when this scope is left, self will be destructed.
    // if there is no shared pointer referencing this, things will crash...
}

void Context::Event::fire(boost::any param, bool immediate) {
    m_context->fire(boost::weak_ptr<Event>(shared_from_this()), param,
        immediate);
}

void Context::handler(boost::weak_ptr<Event> event, boost::any param) {
    auto e = event.lock();
    if(!e) return;
    for(int i = 0; i < (int)e->m_listeners.size(); i ++) {
        auto &listener = e->m_listeners[i];
        listener->m_function(param);

        if(listener->single()) {
            listener->disconnect();
            std::swap(e->m_listeners[i], e->m_listeners.back());
            e->m_listeners.pop_back();
            i --;
            if(e->m_listeners.size() == 0) {
                break;
            }
        }
    }
}

void Context::fire(boost::weak_ptr<Event> event, boost::any params,
    bool immediate) {

    auto e = event.lock();
    if(!e) {
        Message3(State, Error, "Firing removed event");
        return;
    }

    if(!immediate) m_queue.push_back(boost::bind(e->m_handler, params));
    else e->m_handler(params);
}

void Context::fire(std::string name, boost::any params, bool immediate) {
    if(m_events.count(name) == 0) {
        //Message3(State, Error, "No event by name of " << name);
        return;
    }
    auto event = m_events[name];
    if(!immediate) m_queue.push_back(boost::bind(event->m_handler, params));
    else event->m_handler(params);
}

void Context::processQueued() {
    decltype(m_queue) queue_copy;
    std::swap(m_queue, queue_copy);

    for(auto &event : queue_copy) event();
}

}  // namespace State
}  // namespace Kriti
