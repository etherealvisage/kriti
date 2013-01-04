#ifndef KRITI_PHYSICS__UTIL_H
#define KRITI_PHYSICS__UTIL_H


#include "math/Vector.h"

class btVector3;

namespace Kriti {
namespace Physics {

btVector3 toBullet(const Math::Vector &vector);
Math::Vector toMath(const btVector3 &vector);

}  // namespace Physics
}  // namespace Kriti

#endif
