#ifndef KRITI_INTERFACE__CONTEXT_REGISTRY_H
#define KRITI_INTERFACE__CONTEXT_REGISTRY_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "../state/Context.h"

namespace Kriti {
namespace Interface {

class ContextRegistry {
private:
    static boost::shared_ptr<ContextRegistry> s_singleton;
public:
    static boost::shared_ptr<ContextRegistry> instance() {
        if(!s_singleton) {
            s_singleton = boost::make_shared<ContextRegistry>();
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    std::vector<boost::shared_ptr<State::Context>> m_contextList;
    boost::shared_ptr<State::Context> m_sdlContext;
    boost::shared_ptr<State::Context::Event> m_sdlEvent;
public:
    ContextRegistry();

    void push(boost::shared_ptr<State::Context> context)
        { m_contextList.push_back(context); }
    void pop();
    boost::shared_ptr<State::Context> peek() const;

    boost::weak_ptr<State::Context::Event> sdlEvent() const
        { return m_sdlEvent; }

    void run();

    template<typename ...T>
    void fire(std::string name, boost::tuple<T...> params) {
        for(auto &context : m_contextList) {
            context->fire(name, params);
        }
    }
};

}  // namespace Interface
}  // namespace Kriti

#endif
