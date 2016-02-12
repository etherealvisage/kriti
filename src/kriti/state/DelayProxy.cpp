#include "DelayProxy.h"

namespace Kriti {
namespace State {

void DelayProxy::processQueued(TimeValue time) {
    // if no argument is passed, use real time
    if(!time.set()) {
        TimeValue current = TimeValue::current();
        time = current - m_last;
        m_last = current;
    }
    else {
        m_last = m_last + time;
    }

    while(m_events.size()) {
        if(m_events.top().time > m_last) break;
        m_events.top().event();
        m_events.pop();
    }
}

}  // namespace State
}  // namespace Kriti
