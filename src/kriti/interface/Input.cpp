#include "Input.h"
#include "TextInput.h"

namespace Kriti {
namespace Interface {

Input::Input() {
    m_keyboard = new Keyboard();
    m_mouse = new Mouse();
    m_textInput = new TextInput();
}

Input::~Input() {
    delete m_textInput;
    delete m_keyboard;
    delete m_mouse;
}

}  // namespace Interface
}  // namespace Kriti
