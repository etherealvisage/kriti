#ifndef KRITI_EVENT__EVENT_QUEUE_H
#define KRITI_EVENT__EVENT_QUEUE_H

#include <queue>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signal.hpp>

namespace Kriti {
namespace Event {

class EventQueue {
private:
    void trigger(boost::signal<void ()> *signal) { (*signal)(); }

    template<typename T1>
    static void trigger(boost::signal<void (T1)> *signal, T1 t1)
        { (*signal)(t1); }

    template<typename T1, typename T2>
    static void trigger(boost::signal<void (T1, T2)> *signal, T1 t1, T2 t2)
        { (*signal)(t1, t2); }

    template<typename T1, typename T2, typename T3>
    static void trigger(boost::signal<void (T1, T2, T3)> *signal, T1 t1, T2 t2, T3 t3)
        { (*signal)(t1, t2, t3); }
private:
    std::queue<boost::function<void ()>> m_queue;
public:
    void process(int max = -1);

    void enqueue(boost::function<void ()> function);

    template<typename SType>
    void enqueue(SType &signal);
    template<typename SType, typename T1>
    void enqueue(SType &signal, T1 t1);
    template<typename SType, typename T1, typename T2>
    void enqueue(SType &signal, T1 t1, T2 t2);
    template<typename SType, typename T1, typename T2, typename T3>
    void enqueue(SType &signal, T1 t1, T2 t2, T3 t3);
};

template<typename SType>
void EventQueue::enqueue(SType &signal) {
    enqueue(boost::bind(&EventQueue::trigger, &signal));
}

template<typename SType, typename T1>
void EventQueue::enqueue(SType &signal, T1 t1) {
    enqueue(boost::bind(&EventQueue::trigger<T1>, &signal, t1));
}

template<typename SType, typename T1, typename T2>
void EventQueue::enqueue(SType &signal, T1 t1, T2 t2) {
    enqueue(boost::bind(&EventQueue::trigger<T1, T2>, &signal, t1, t2));
}

template<typename SType, typename T1, typename T2, typename T3>
void EventQueue::enqueue(SType &signal, T1 t1, T2 t2, T3 t3) {
    enqueue(boost::bind(&EventQueue::trigger<T1, T2, T3>,
        &signal, t1, t2, t3));
}

}  // namespace Event
}  // namespace Kriti

#endif
