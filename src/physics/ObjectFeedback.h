#ifndef KRITI_PHYSICS__OBJECT_FEEDBACK_H
#define KRITI_PHYSICS__OBJECT_FEEDBACK_H

#include "math/Vector.h"
#include "math/Quaternion.h"

namespace Kriti {
namespace Physics {

class ObjectFeedback {
public:
    virtual ~ObjectFeedback() {}

    virtual void transformUpdated(Math::Vector location,
        Math::Quaternion orientation) = 0;
};

}  // namespace Physics
}  // namespace Kriti

#endif
