#ifndef KRITI_INTERFACE__TEXT_INPUT_H
#define KRITI_INTERFACE__TEXT_INPUT_H

#include <boost/shared_ptr.hpp>

#include <SDL_events.h>

namespace Kriti {
namespace Interface {

class TextInput {
public:
    TextInput();

    static void begin();
    static void end();
private:
    void textEvent(SDL_Event event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
