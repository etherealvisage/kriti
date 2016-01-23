#include <btBulletDynamicsCommon.h>

#include "Util.h"

namespace Kriti {
namespace Bullet {

btVector3 toBullet(const Math::Vector &vector) {
    return btVector3(vector.x(), vector.y(), vector.z());
}

Math::Vector toMath(const btVector3 &vector) {
    return Math::Vector(vector.x(), vector.y(), vector.z());
}

btQuaternion toBullet(const Math::Quaternion &quaternion) {
    Math::Vector axis;
    double angle;
    quaternion.toAxisAngle(axis, angle);
    return btQuaternion(toBullet(axis), angle);
}

Math::Quaternion toMath(const btQuaternion &quaternion) {
    return Math::Quaternion(toMath(quaternion.getAxis()),
        quaternion.getAngle());
}

}  // namespace Bullet
}  // namespace Kriti
