#ifndef KRITI_INTERFACE__INPUT_DEVICE_H
#define KRITI_INTERFACE__INPUT_DEVICE_H

#include <SDL.h>

namespace Kriti {
namespace Interface {

class InputDevice {
public:
    virtual ~InputDevice() {}

    virtual void poll() = 0;

    virtual void reloadMapping() = 0;

    virtual void handleEvent(SDL_Event *event) = 0;
};

}  // namespace Interface
}  // namespace Kriti

#endif
