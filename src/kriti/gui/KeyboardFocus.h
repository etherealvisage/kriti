#ifndef KRITI_GUI__KEYBOARD_FOCUS_H
#define KRITI_GUI__KEYBOARD_FOCUS_H

#include <boost/shared_ptr.hpp>

#include "KeyboardFocusTarget.h"

#include "../state/Context.fwd"

#include "../Singleton.h"

namespace Kriti {
namespace GUI {

class KeyboardFocus : public Singleton<KeyboardFocus> {
    friend class Singleton<KeyboardFocus>;
private:
    boost::shared_ptr<KeyboardFocusTarget> m_target;
private:
    KeyboardFocus() {}
    ~KeyboardFocus() {}
public:
    void changeFocus(boost::shared_ptr<KeyboardFocusTarget> target);
    void clearFocus()
        { changeFocus(boost::shared_ptr<KeyboardFocusTarget>()); }
    bool focused() const { return !!m_target; }

    void keyPressed(SDL_Keycode key);
    void keyReleased(SDL_Keycode key);
    void textEntered(std::string text);
};

}  // namespace GUI
}  // namespace Kriti

#endif
