#include <string>

#include "Vector.h"
#include "StreamAsString.h"

namespace Kriti {
namespace Math {

std::string Vector::toString() const {
    return StreamAsString() << "(" << m_x << "," << m_y << "," << m_z << ")";
}

}  // namespace Math
}  // namespace Kriti
