#include "Keyboard.h"
#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

Keyboard::Keyboard() {
    State::Context::addListener(ContextRegistry::get()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&Keyboard::keyEvent, this, _1)));
}

void Keyboard::keyEvent(SDL_Event event) {
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        ContextRegistry::get()->fire("key_down",
            boost::make_tuple(event.key.keysym.sym));
    }
    else if(event.type == SDL_KEYUP) {
        ContextRegistry::get()->fire("key_up",
            boost::make_tuple(event.key.keysym.sym));
    }
}

}  // namespace Interface
}  // namespace Kriti
