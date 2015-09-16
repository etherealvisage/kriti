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

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/bind/apply.hpp>
#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

#include "../MessageSystem.h"
#include "../TupleUtil.h"

namespace Kriti {
namespace State {

class Context {
private:
    std::map<std::string, std::string> m_eventTypes;
    std::map<std::string, boost::function<void (boost::any)>> m_handlers;
    std::map<std::string, std::vector<boost::function<void (boost::any)>>> m_listeners;
    std::vector<boost::function<void ()>> m_events;
private:
    template<typename ...T>
    static void makeWrapper(boost::function<void (T...)> function,
        boost::any param) {

        TupleUtil::apply(function, boost::any_cast<boost::tuple<T...>>(param));
    }

    template<typename ...T>
    void handler(std::string name, boost::any param) {
        for(auto &listener : m_listeners[name]) listener(param);
    }
public:
    template<typename ...T>
    void addEvent(std::string name) {
        if(m_eventTypes.count(name) != 0) {
            Message3(State, Error, "Trying to add event that already exists!");
            return;
        }
        m_eventTypes[name] = typeid(boost::tuple<T...>).name();
        m_handlers[name] = boost::bind(&Context::handler, this, name, _1);
    }

    template<typename ...T>
    void addListener(std::string name, boost::function<void (T...)> function) {
        if(m_handlers.count(name) == 0) {
            addEvent<T...>(name);
        }
        else if(typeid(boost::tuple<T...>).name() != m_eventTypes[name]) {
            Message3(State, Error, "Type mismatch when adding listener "
                << name);
            return;
        }
        m_listeners[name].push_back(boost::bind(makeWrapper<T...>, function,
            _1));
    }

    void addListener(std::string name, Context *context,
        std::string contextName) {

        if(m_eventTypes.count(name) == 0) {
            Message3(State, Error,
                "Trying to add context listener for nonexistent event");
            return;
        }
        if(context->m_eventTypes.count(contextName) == 0) {
            context->m_eventTypes[contextName] = m_eventTypes[name];
            context->m_handlers[name] = boost::bind(&Context::handler, context,
                contextName, _1);
        }

        m_listeners[name].push_back(boost::bind(&Context::fire,
            context, contextName, _1, false));
    }

    void addListener(std::string name, Context *context) {
        addListener(name, context, name);
    }

    void fire(std::string name, boost::any params, bool immediate = false);
    
    void processQueued();
};

}  // namespace State
}  // namespace Kriti

#endif
