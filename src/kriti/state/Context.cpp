#include "Context.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace State {

void Context::fire(std::string name, boost::any params, bool immediate) {
    if(m_handlers.count(name) == 0) {
        Message3(State, Error, "No event by name of " << name);
        return;
    }
    if(!immediate) m_events.push_back(boost::bind(m_handlers[name], params));
    else m_handlers[name](params);
}

void Context::processQueued() {
    decltype(m_events) events_copy;
    std::swap(m_events, events_copy);

    for(auto &event : events_copy) event();
}

}  // namespace State
}  // namespace Kriti
