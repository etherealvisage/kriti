#ifndef KRITI_INTERFACE__INPUT_H
#define KRITI_INTERFACE__INPUT_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "Keyboard.h"
#include "Mouse.h"
#include "TextInput.h"

#include "../Singleton.h"

namespace Kriti {
namespace Interface {

class Input : public Singleton<Input> {
    friend class Singleton<Input>;
private:
    Keyboard *m_keyboard;
    Mouse *m_mouse;
    TextInput *m_textInput;
private:
    Input();
    ~Input();
};

}  // namespace Interface
}  // namespace Kriti

#endif
