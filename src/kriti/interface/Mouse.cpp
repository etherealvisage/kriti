#include <SDL_mouse.h>

#include "Mouse.h"
#include "ContextRegistry.h"
#include "Video.h"

namespace Kriti {
namespace Interface {

Mouse::Mouse() {
    State::Context::addListener(ContextRegistry::get()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&Mouse::mouseEvent, this, _1)));
}

void Mouse::mouseEvent(SDL_Event event) {
    if(event.type == SDL_MOUSEMOTION) {
        double x = event.motion.x, y = event.motion.y;
        x /= Video::get()->width(); x *= Video::get()->aspectRatio();
        y /= Video::get()->height();
        y = 1-y; // invert y-axis
        ContextRegistry::get()->fire("mouseMoved",
            boost::make_tuple(x, y));
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN
        || event.type == SDL_MOUSEBUTTONUP) {

        int button = 0;
        switch(event.button.button) {
        case SDL_BUTTON_LEFT:
            button = 0;
            break;
        case SDL_BUTTON_MIDDLE:
            button = 1;
            break;
        case SDL_BUTTON_RIGHT:
            button = 2;
            break;
        default:
            button = 0;
            break;
        }

        if(event.type == SDL_MOUSEBUTTONUP)
            ContextRegistry::get()->fire("mouseUp",
                boost::make_tuple(button));
        else
            ContextRegistry::get()->fire("mouseDown",
                boost::make_tuple(button));
    }
    else if(event.type == SDL_MOUSEWHEEL) {
        int x = event.wheel.x, y = event.wheel.y;
        ContextRegistry::get()->fire("mouseWheel",
            boost::make_tuple(x, y));
    }
}

}  // namespace Interface
}  // namespace Kriti
