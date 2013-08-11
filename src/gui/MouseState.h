#ifndef KRITI_GUI__MOUSE_STATE_H
#define KRITI_GUI__MOUSE_STATE_H

#include "math/Vector.h"

namespace Kriti {
namespace GUI {

class MouseState {
private:
    bool m_posSet;
    Math::Vector m_pos;
public:
    MouseState() : m_posSet(false) {}

    Math::Vector pos() const { return m_pos; }
    void setPos(Math::Vector pos) { m_pos = pos, m_posSet = true; }
    bool posSet() const { return m_posSet; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
