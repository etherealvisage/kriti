#ifndef KRITI_GUI__MOUSE_STATE_H
#define KRITI_GUI__MOUSE_STATE_H

#include "math/Vector.h"

namespace Kriti {
namespace GUI {

class MouseState {
private:
    bool m_posSet;
    Math::Vector m_pos;

    bool m_buttons[3];
public:
    MouseState() : m_posSet(false)
        { m_buttons[0] = m_buttons[1] = m_buttons[2] = false; }

    Math::Vector pos() const { return m_pos; }
    void setPos(Math::Vector pos) { m_pos = pos, m_posSet = true; }
    bool posSet() const { return m_posSet; }

    bool button(int which) const { return m_buttons[which]; }
    void setButton(int which, bool value) { m_buttons[which] = value; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
