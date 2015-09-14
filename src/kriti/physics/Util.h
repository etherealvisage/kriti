#ifndef KRITI_PHYSICS__UTIL_H
#define KRITI_PHYSICS__UTIL_H

#include "../math/Vector.h"
#include "../math/Quaternion.h"

class btVector3;
class btQuaternion;

namespace Kriti {
namespace Physics {

btVector3 toBullet(const Math::Vector &vector);
Math::Vector toMath(const btVector3 &vector);

btQuaternion toBullet(const Math::Quaternion &quaternion);
Math::Quaternion toMath(const btQuaternion &quaternion);

}  // namespace Physics
}  // namespace Kriti

#endif
