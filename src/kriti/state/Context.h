#ifndef KRITI_STATE__CONTEXT_H
#define KRITI_STATE__CONTEXT_H

/* NOTES:
     - immediately-fired events will not propagate immediately to other
        Contexts.
*/

#include <map>
#include <vector>
#include <string>
#include <typeinfo>
#include <set>

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/bind/apply.hpp>
#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../MessageSystem.h"
#include "../TupleUtil.h"

namespace Kriti {
namespace State {

class Context {
public:
    class Event;
    class Listener {
    private:
        friend class Context;
        boost::weak_ptr<Event> m_event;
        boost::function<void (boost::any)> m_function;
    public:
        void disconnect();
    };

    class Event : public boost::enable_shared_from_this<Event> {
    private:
        friend class Context;
        Context *m_context;
        std::string m_name;
        std::string m_eventType;
        boost::function<void (boost::any)> m_handler;
        std::vector<boost::shared_ptr<Listener>> m_listeners;
    public:
        void fire(boost::any param, bool immediate = false);
    };
private:
    std::map<std::string, boost::shared_ptr<Event>> m_events;
    std::set<boost::shared_ptr<Event>> m_anonymousEvents;
    std::vector<boost::function<void ()>> m_queue;
private:
    template<typename ...T>
    static void makeWrapper(boost::function<void (T...)> function,
        boost::any param) {

        TupleUtil::apply(function, boost::any_cast<boost::tuple<T...>>(param));
    }

    template<typename ...T>
    static void handler(boost::weak_ptr<Event> event, boost::any param) {
        auto e = event.lock();
        if(!e) return;
        for(auto &listener : e->m_listeners) listener->m_function(param);
    }
public:
    template<typename ...T>
    boost::weak_ptr<Event> addEvent(std::string name) {
        if(m_events.count(name)) {
            Message3(State, Error, "Trying to add event that already exists!");
            return boost::weak_ptr<Event>();
        }

        auto event = boost::make_shared<Event>();
        event->m_context = this;
        event->m_name = name;
        event->m_eventType = typeid(boost::tuple<T...>).name();
        event->m_handler = boost::bind(&Context::handler, event, _1);
        m_events[name] = event;
        
        return event;
    }

    template<typename ...T>
    boost::weak_ptr<Event> addEvent() {
        auto event = boost::make_shared<Event>();
        event->m_context = this;
        event->m_eventType = typeid(boost::tuple<T...>).name();
        event->m_handler = boost::bind(&Context::handler, event, _1);
        
        return event;
    }

    boost::weak_ptr<Event> getEvent(std::string name) {
        if(m_events.count(name)) return m_events[name];
        return boost::weak_ptr<Event>();
    }

    template<typename ...T>
    boost::weak_ptr<Listener> addListener(std::string name,
        boost::function<void (T...)> function) {

        if(m_events.count(name) == 0) {
            addEvent<T...>(name);
        }

        auto event = m_events[name];
        return addListener(event, function);
    }

    template<typename ...T>
    static boost::weak_ptr<Listener> addListener(boost::weak_ptr<Event> event, 
        boost::function<void (T...)> function) {

        auto e = event.lock();
        if(!e) return boost::weak_ptr<Listener>();

        if(typeid(boost::tuple<T...>).name() != e->m_eventType) {
            Message3(State, Error, "Type mismatch when adding listener");
            return boost::weak_ptr<Listener>();
        }

        auto listener = boost::make_shared<Listener>();
        listener->m_event = event;
        listener->m_function = boost::bind(makeWrapper<T...>, function, _1);
        e->m_listeners.push_back(listener);
        return listener;
    }

    boost::weak_ptr<Listener> addListener(std::string name, Context *context,
        std::string contextName) {

        if(m_events.count(name) == 0) {
            Message3(State, Error,
                "Trying to add context listener for nonexistent event");
            return boost::weak_ptr<Listener>();
        }

        auto own_event = m_events[name];
        if(context->m_events.count(contextName) == 0) {
            auto event = boost::make_shared<Event>();
            event->m_context = context;
            event->m_eventType = own_event->m_eventType;
            event->m_handler = boost::bind(&Context::handler, event, _1);
            context->m_events[name] = event;
        }

        auto listener = boost::make_shared<Listener>();
        listener->m_event = own_event;
        listener->m_function = boost::bind(
            static_cast<void (Context::*)(std::string, boost::any, bool)>(
                &Context::fire),
            context, contextName, _1, false);
        own_event->m_listeners.push_back(listener);

        return listener;
    }

    boost::weak_ptr<Listener> addListener(std::string name, Context *context) {
        return addListener(name, context, name);
    }

    void fire(boost::weak_ptr<Event> event, boost::any params,
        bool immediate = false);
    void fire(std::string name, boost::any params, bool immediate = false);
    
    void processQueued();
};

}  // namespace State
}  // namespace Kriti

#endif
