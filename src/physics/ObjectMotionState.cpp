#include "ObjectMotionState.h"
#include "Util.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

void ObjectMotionState::setWorldTransform(const btTransform &transform) {
    btDefaultMotionState::setWorldTransform(transform);

    auto location = toMath(transform.getOrigin());
    auto orientation = toMath(transform.getRotation());
    for(auto feedback : m_feedbacks) {
        feedback->transformUpdated(location, orientation);
    }
}

}  // namespace Physics
}  // namespace Kriti
