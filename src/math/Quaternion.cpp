#include "Quaternion.h"

namespace Kriti {
namespace Math {

Quaternion::Quaternion(const Vector &axis, double angle) {
    m_s = std::cos(angle/2.0);
    m_v = axis*std::sin(angle/2.0);
}

void Quaternion::toAxisAngle(Vector &axis, double &angle) const {
    angle = 2*std::acos(m_s);
    if(std::abs(angle) > Constants::Epsilon) {
        axis = m_v / std::sin(angle/2.0);
    }
    /* No rotation, so there is no axis . . . */
    else axis = Vector();
}

}  // namespace Math
}  // namespace Kriti
