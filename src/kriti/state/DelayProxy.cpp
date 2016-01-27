#include "DelayProxy.h"

namespace Kriti {
namespace State {

void DelayProxy::processQueued() {
    TimeValue current = TimeValue::current();

    while(m_events.size()) {
        if(m_events.top().time > current) break;
        m_events.top().event();
        m_events.pop();
    }
}

}  // namespace State
}  // namespace Kriti
