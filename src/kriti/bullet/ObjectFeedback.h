#ifndef KRITI_BULLET__OBJECT_FEEDBACK_H
#define KRITI_BULLET__OBJECT_FEEDBACK_H

#include "../math/Vector.h"
#include "../math/Quaternion.h"

namespace Kriti {
namespace Bullet {

class ObjectFeedback {
public:
    virtual ~ObjectFeedback() {}

    virtual void transformUpdated(Math::Vector location,
        Math::Quaternion orientation) = 0;
};

}  // namespace Bullet
}  // namespace Kriti

#endif
