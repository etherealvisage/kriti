#include "Input.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<Input> Input::s_singleton;

Input::Input() {
    m_keyboard = new Keyboard();
    m_mouse = new Mouse();
}

}  // namespace Interface
}  // namespace Kriti