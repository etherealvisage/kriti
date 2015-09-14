#include <SDL.h>

#include "Mouse.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Interface {

void Mouse::poll() {
    while(m_eventQueue.size() > 0) {
        auto event = m_eventQueue.front();
        m_eventQueue.pop();


        if(event.type == SDL_MOUSEMOTION) {
            m_router->fire(m_router->motionSignal(),
                static_cast<int>(event.motion.x),
                static_cast<int>(event.motion.y));
        }
        else {
            MouseRouter::ButtonSignalName which;
            switch(event.button.button) {
            case SDL_BUTTON_LEFT:
                which = MouseRouter::LeftButton;
                break;
            case SDL_BUTTON_MIDDLE:
                which = MouseRouter::MiddleButton;
                break;
            case SDL_BUTTON_RIGHT:
                which = MouseRouter::RightButton;
                break;
            default:
                which = MouseRouter::ButtonSignalNames;
                break;
            }

            // skip unknown buttons
            if(which == MouseRouter::ButtonSignalNames) continue;

            m_router->fire(m_router->buttonSignal(which),
                event.type == SDL_MOUSEBUTTONDOWN);
        }
    }
}

void Mouse::handleEvent(SDL_Event *event) {
    if(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN
        || event->type == SDL_MOUSEBUTTONUP) {

        m_eventQueue.push(*event);
    }
}

}  // namespace Interface
}  // namespace Kriti
