#include <SDL.h>

#include "../state/DelayProxy.h"

#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<ContextRegistry> ContextRegistry::s_singleton;

ContextRegistry::ContextRegistry() {
    m_sdlContext = boost::make_shared<State::Context>();
    m_sdlEvent = m_sdlContext->addEvent<SDL_Event>().lock();
}

void ContextRegistry::pop() {
    if(!m_contextList.empty()) m_contextList.pop_back();
} 

boost::shared_ptr<State::Context> ContextRegistry::peek() const {
    if(!m_contextList.empty()) return m_contextList.back();
    return boost::shared_ptr<State::Context>();
} 

void ContextRegistry::run() {
    while(!m_contextList.empty()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            m_sdlEvent->fire(boost::make_tuple(event));
        }
        m_sdlContext->processQueued();

        State::DelayProxy::instance()->processQueued();

        fire("new_frame", boost::make_tuple());

        for(auto &context : m_contextList) {
            context->processQueued();
        }
    }
}

}  // namespace Interface
}  // namespace Kriti
