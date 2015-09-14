#include "KeyboardRouter.h"

namespace Kriti {
namespace Interface {

const char *KeyboardRouter::s_configNames[] = {
#define KEYBOARD_SIGNAL(e, s) #s,
#include "KeyboardSignals.h"
#undef KEYBOARD_SIGNAL
    NULL
};

}  // namespace Interface
}  // namespace Kriti
