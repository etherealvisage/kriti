#ifndef KRITI_EVENT__EVENT_QUEUE_H
#define KRITI_EVENT__EVENT_QUEUE_H

#include <queue>

#include <boost/bind.hpp>
#include <boost/function.hpp>

namespace Kriti {
namespace Event {

class EventQueue {
private:
    std::queue<boost::function<void ()>> m_queue;
public:
    EventQueue();
    ~EventQueue();

    void process(int max = -1);

    void enqueue(boost::function<void ()> function);

    template<typename T1>
    void enqueue(boost::function<void (T1)> function, T1 &t1);

    template<typename T1, typename T2>
    void enqueue(boost::function<void (T1, T2)> function, T1 &t1, T2 &t2);

    template<typename T1, typename T2, typename T3>
    void enqueue(boost::function<void (T1, T2, T3)> function, T1 &t1, T2 &t2,
        T3 &t3);
};

template<typename T1>
void EventQueue::enqueue(boost::function<void (T1)> function, T1 &t1) {

    enqueue(boost::bind(function, t1));
}

template<typename T1, typename T2>
void EventQueue::enqueue(boost::function<void (T1, T2)> function, T1 &t1,
    T2 &t2) {

    enqueue(boost::bind(function, t1, t2));
}

template<typename T1, typename T2, typename T3>
void EventQueue::enqueue(boost::function<void (T1, T2, T3)> function, T1 &t1,
    T2 &t2, T3 &t3) {

    enqueue(boost::bind(function, t1, t2, t3));
}

}  // namespace Event
}  // namespace Kriti

#endif
