#ifndef KRITI_INTERFACE__MOUSE_H
#define KRITI_INTERFACE__MOUSE_H

#include <SDL_events.h>

namespace Kriti {
namespace Interface {

class Mouse {
public:
    Mouse();
private:
    void mouseEvent(SDL_Event event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
