#include "Mouse.h"
#include "ContextRegistry.h"
#include "Video.h"

namespace Kriti {
namespace Interface {

Mouse::Mouse() {
    State::Context::addListener(ContextRegistry::instance()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&Mouse::mouseEvent, this, _1)));
}

void Mouse::mouseEvent(SDL_Event event) {
    if(event.type == SDL_MOUSEMOTION) {
        double x = event.motion.x, y = event.motion.y;
        x /= Video::instance()->width();
        y /= Video::instance()->height();
        ContextRegistry::instance()->fire("mouse_moved",
            boost::make_tuple(x, y));
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN) {
        ContextRegistry::instance()->fire("mouse_down",
            boost::make_tuple(static_cast<int>(event.button.button)));
    }
    else if(event.type == SDL_MOUSEBUTTONUP) {
        ContextRegistry::instance()->fire("mouse_up",
            boost::make_tuple(static_cast<int>(event.button.button)));
    }
}

}  // namespace Interface
}  // namespace Kriti
