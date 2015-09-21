#include "Keyboard.h"
#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

Keyboard::Keyboard() {
    State::Context::addListener(ContextRegistry::instance()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&Keyboard::keyEvent, this, _1)));
}

void Keyboard::keyEvent(SDL_Event event) {
    if(event.type == SDL_KEYDOWN) {
        ContextRegistry::instance()->fire("key_down",
            boost::make_tuple(event.key.keysym.sym));
    }
    else if(event.type == SDL_KEYUP) {
        ContextRegistry::instance()->fire("key_up",
            boost::make_tuple(event.key.keysym.sym));
    }
}

}  // namespace Interface
}  // namespace Kriti
