#ifndef KRITI_INTERFACE__CONTEXT_REGISTRY_H
#define KRITI_INTERFACE__CONTEXT_REGISTRY_H

#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "../state/Context.h"

#include "../Singleton.h"

namespace Kriti {
namespace Interface {

class ContextRegistry : public Singleton<ContextRegistry> {
    friend class Singleton<ContextRegistry>;
private:
    std::vector<boost::shared_ptr<State::Context>> m_contextList;
    boost::shared_ptr<State::Context> m_sdlContext;
    boost::shared_ptr<State::Context::Event> m_sdlEvent;
private:
    ContextRegistry();
    ~ContextRegistry() {}
public:
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
