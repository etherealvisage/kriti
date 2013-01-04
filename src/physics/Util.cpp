#include <btBulletDynamicsCommon.h>

#include "Util.h"

namespace Kriti {
namespace Physics {

btVector3 toBullet(const Math::Vector &vector) {
    return btVector3(vector.x(), vector.y(), vector.z());
}

Math::Vector toMath(const btVector3 &vector) {
    return Math::Vector(vector.x(), vector.y(), vector.z());
}

}  // namespace Physics
}  // namespace Kriti
