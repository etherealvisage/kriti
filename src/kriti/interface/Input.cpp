#include "Input.h"
#include "TextInput.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<Input> Input::s_singleton;

Input::Input() {
    m_keyboard = new Keyboard();
    m_mouse = new Mouse();

    TextInput::instance();
}

Input::~Input() {
    delete m_keyboard;
    delete m_mouse;
    TextInput::destroy();
}

}  // namespace Interface
}  // namespace Kriti
