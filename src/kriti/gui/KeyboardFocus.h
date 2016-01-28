#ifndef KRITI_GUI__KEYBOARD_FOCUS_H
#define KRITI_GUI__KEYBOARD_FOCUS_H

#include <boost/shared_ptr.hpp>

#include "KeyboardFocusTarget.h"

#include "../state/Context.fwd"

#include "../Globals.h"

namespace Kriti {
namespace GUI {

class KeyboardFocus { KRITI_GLOBAL(KeyboardFocus)
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
