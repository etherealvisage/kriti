#include "EventQueue.h"

namespace Kriti {
namespace Event {

void EventQueue::process(int max) {
    /* Only process events currently in the queue. */
    int size = m_queue.size();
    for(int i = 0; (i < max || max == -1) && i < size; i ++) {
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
