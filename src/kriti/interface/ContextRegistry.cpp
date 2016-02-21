#include <SDL.h>

#include "../state/DelayProxy.h"

#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

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
    Kriti::TimeValue lastFrame;
    while(!m_contextList.empty()) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            m_sdlEvent->fire(boost::make_tuple(event));
        }
        m_sdlContext->processQueued();

        State::DelayProxy::get()->processQueued();

        Kriti::TimeValue thisFrame = Kriti::TimeValue::current();
        if(!lastFrame.set()) lastFrame = thisFrame;
        fire("newFrame", boost::make_tuple(thisFrame-lastFrame));
        lastFrame = thisFrame;

        for(auto &context : m_contextList) {
            context->processQueued();
        }
    }
}

}  // namespace Interface
}  // namespace Kriti
