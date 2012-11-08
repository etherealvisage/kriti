#include "Keyboard.h"

namespace Kriti {
namespace Interface {

void Keyboard::poll() {
    while(m_eventQueue.size() > 0) {
        auto event = m_eventQueue.front();
        m_eventQueue.pop();

        std::cout << "Key event!" << std::endl;
        auto signal = m_keyMapping[event.key.keysym.sym];
        // fire the signal if it is mapped.
        if(signal != NULL) {
            Event::EventRouter::fire(*signal, event.type == SDL_KEYDOWN);
        }
    }
}

void Keyboard::reloadMapping() {
    m_keyMapping.clear();
}

void Keyboard::handleEvent(SDL_Event *event) {
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
        m_eventQueue.push(*event);
    }
}

}  // namespace Interface
}  // namespace Kriti
