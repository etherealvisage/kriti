#include "EventQueue.h"

namespace Kriti {
namespace Event {

void EventQueue::process(int max) {
    for(int i = 0; (i < max || max == -1) && m_queue.size() > 0; i ++) {
        auto f = m_queue.front();
        m_queue.pop();

        f();
    }
}

void EventQueue::enqueue(boost::function<void ()> function) {
    m_queue.push(function);
}

}  // namespace Event
}  // namespace Kriti
