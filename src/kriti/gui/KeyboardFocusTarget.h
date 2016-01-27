#ifndef KRITI_GUI__KEYBOARD_FOCUS_TARGET_H
#define KRITI_GUI__KEYBOARD_FOCUS_TARGET_H

#include <string>

#include "KeyboardFocus.fwd"

#include "../interface/Keyboard.h" // for SDL things

namespace Kriti {
namespace GUI {

class KeyboardFocusTarget {
public:
    virtual ~KeyboardFocusTarget() {}

    virtual bool wantsFocus() = 0;
    virtual bool wantsText() = 0;
    virtual void lostFocus(KeyboardFocus &focus) = 0;
    virtual void gainedFocus(KeyboardFocus &focus) = 0;

    virtual void keyPressed(SDL_Keycode key) = 0;
    virtual void keyReleased(SDL_Keycode key) = 0;
    virtual void textEntered(std::string text) = 0;
};

}  // namespace GUI
}  // namespace Kriti

#endif
