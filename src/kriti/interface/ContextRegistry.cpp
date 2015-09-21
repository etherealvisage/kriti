#include <SDL.h>

#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<ContextRegistry> ContextRegistry::s_singleton;

ContextRegistry::ContextRegistry() {
    m_sdlContext = boost::make_shared<State::Context>();
    m_sdlEvent = m_sdlContext->addEvent<SDL_Event>().lock();
}

void ContextRegistry::run() {
    while(!m_contextList.empty()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            m_sdlContext->fire(m_sdlEvent, boost::make_tuple(event));
        }

        for(auto &context : m_contextList) {
            context->processQueued();
        }
    }
}

}  // namespace Interface
}  // namespace Kriti
