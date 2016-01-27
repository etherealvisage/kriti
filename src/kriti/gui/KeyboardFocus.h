#ifndef KRITI_GUI__KEYBOARD_FOCUS_H
#define KRITI_GUI__KEYBOARD_FOCUS_H

#include <boost/shared_ptr.hpp>

#include "kriti/state/Context.fwd"

#include "KeyboardFocusTarget.h"

namespace Kriti {
namespace GUI {

/* NOTE: it's not good if multiple KeyboardFocuses are being used at the same
    time. This should either be stored in a singleton or be singleton itself */
class KeyboardFocus {
private:
    boost::shared_ptr<KeyboardFocusTarget> m_target;
public:
    void changeFocus(boost::shared_ptr<KeyboardFocusTarget> target);
    void clearFocus()
        { changeFocus(boost::shared_ptr<KeyboardFocusTarget>()); }

    void keyPressed(SDL_Keycode key);
    void keyReleased(SDL_Keycode key);
    void textEntered(std::string text);
};

}  // namespace GUI
}  // namespace Kriti

#endif
