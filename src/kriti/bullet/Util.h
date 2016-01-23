#ifndef KRITI_BULLET__UTIL_H
#define KRITI_BULLET__UTIL_H

#include "../math/Vector.h"
#include "../math/Quaternion.h"

class btVector3;
class btQuaternion;

namespace Kriti {
namespace Bullet {

btVector3 toBullet(const Math::Vector &vector);
Math::Vector toMath(const btVector3 &vector);

btQuaternion toBullet(const Math::Quaternion &quaternion);
Math::Quaternion toMath(const btQuaternion &quaternion);

}  // namespace Bullet
}  // namespace Kriti

#endif
