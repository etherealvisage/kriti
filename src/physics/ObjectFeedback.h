#ifndef KRITI_PHYSICS__OBJECT_FEEDBACK_H
#define KRITI_PHYSICS__OBJECT_FEEDBACK_H

#include <btBulletDynamicsCommon.h>

#include "math/Vector.h"
#include "math/Quaternion.h"

namespace Kriti {
namespace Physics {

class ObjectFeedback : public btDefaultMotionState {
public:
    virtual ~ObjectFeedback() {}

    virtual void setWorldTransform(const btTransform &transform);
protected:
    virtual void updateTransform(Math::Vector location,
        Math::Quaternion orientation) = 0;
};

}  // namespace Physics
}  // namespace Kriti

#endif
