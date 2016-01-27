#include <SDL_mouse.h>

#include "Mouse.h"
#include "ContextRegistry.h"
#include "Video.h"

#include "../Globals.h"

namespace Kriti {
namespace Interface {

Mouse::Mouse() {
    State::Context::addListener(Global<ContextRegistry>()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&Mouse::mouseEvent, this, _1)));
}

void Mouse::mouseEvent(SDL_Event event) {
    if(event.type == SDL_MOUSEMOTION) {
        double x = event.motion.x, y = event.motion.y;
        x /= Global<Video>()->width(); x *= Global<Video>()->aspectRatio();
        y /= Global<Video>()->height();
        y = 1-y; // invert y-axis
        Global<ContextRegistry>()->fire("mouse_moved",
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
            Global<ContextRegistry>()->fire("mouse_up",
                boost::make_tuple(button));
        else
            Global<ContextRegistry>()->fire("mouse_down",
                boost::make_tuple(button));
    }
    else if(event.type == SDL_MOUSEWHEEL) {
        int x = event.wheel.x, y = event.wheel.y;
        Global<ContextRegistry>()->fire("mouse_wheel",
            boost::make_tuple(x, y));
    }
}

}  // namespace Interface
}  // namespace Kriti
