#include "ObjectFeedback.h"

#include "Util.h"

namespace Kriti {
namespace Physics {

void ObjectFeedback::setWorldTransform(const btTransform &transform) {
    btDefaultMotionState::setWorldTransform(transform);

    updateTransform(toMath(transform.getOrigin()),
        toMath(transform.getRotation()));
}

}  // namespace Physics
}  // namespace Kriti
