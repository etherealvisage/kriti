#ifndef KRITI_INTERFACE__KEYBOARD_H
#define KRITI_INTERFACE__KEYBOARD_H

#include <SDL_events.h>

namespace Kriti {
namespace Interface {

class Keyboard {
public:
    Keyboard();
private:
    void keyEvent(SDL_Event event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
