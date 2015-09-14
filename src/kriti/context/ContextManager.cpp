#include "ContextManager.h"
#include "../interface/DeviceManager.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Context {

ContextManager *ContextManager::s_singleton;

void ContextManager::addContext(AbstractContext *context) {
    std::string name = context->contextName();

    m_contextMap[name] = context;
}

void ContextManager::pushContext(std::string name) {
    if(m_contextStack.size()) m_contextStack.back()->deactivate();
    m_contextStack.push_back(m_contextMap[name]);
    m_contextStack.back()->activate();
}

void ContextManager::popContext() {
    m_contextStack.pop_back();
    if(m_contextStack.size()) m_contextStack.back()->activate();
}

void ContextManager::loop() {
    while(m_contextStack.size()) {
        m_contextStack.back()->run();
        
        // should this be moved somewhere else?
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            Interface::DeviceManager::instance()->handleEvent(&event);
        }

        Interface::DeviceManager::instance()->pollDevices();
    }
}

}  // namespace Context
}  // namespace Kriti
