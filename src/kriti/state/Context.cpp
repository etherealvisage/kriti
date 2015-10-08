#include <iostream> // debugging
#include <algorithm>

#include "Context.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace State {

void Context::Listener::disconnect() {
    auto event = m_event.lock();
    if(!event) return;

    auto &l = event->m_listeners;
    l.erase(std::remove_if(l.begin(), l.end(),
        [this](boost::shared_ptr<Listener> &x){ return x.get() == this; } ),
        l.end());
}

void Context::Event::fire(boost::any param, bool immediate) {
    m_context->fire(boost::weak_ptr<Event>(shared_from_this()), param,
        immediate);
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
