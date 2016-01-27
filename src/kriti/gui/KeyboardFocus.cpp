#include "KeyboardFocus.h"

#include "../interface/TextInput.h"

namespace Kriti {
namespace GUI {

void KeyboardFocus::changeFocus(
    boost::shared_ptr<KeyboardFocusTarget> target) {

    if(m_target) m_target->lostFocus(*this);

    m_target = target;

    if(!m_target) return;
    
    if(m_target->wantsFocus()) {
        m_target->gainedFocus(*this);

        if(m_target->wantsText()) {
            Interface::TextInput::begin();
        }
        else {
            Interface::TextInput::end();
        }
    }
}

void KeyboardFocus::keyPressed(SDL_Keycode key) {
    if(m_target) m_target->keyPressed(key);
}

void KeyboardFocus::keyReleased(SDL_Keycode key) {
    if(m_target) m_target->keyReleased(key);
}

void KeyboardFocus::textEntered(std::string text) {
    if(m_target) m_target->textEntered(text);
}

}  // namespace GUI
}  // namespace Kriti
