#include "DelayProxy.h"

namespace Kriti {
namespace State {

boost::shared_ptr<DelayProxy> DelayProxy::s_singleton;

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
