#ifndef KRITI_PHYSICS__PHYSICAL_OBJECT_H
#define KRITI_PHYSICS__PHYSICAL_OBJECT_H

#include <boost/shared_ptr.hpp>

#include "math/Vector.h"
#include "math/Quaternion.h"

class btRigidBody;

namespace Kriti {
namespace Physics {

class ObjectFeedback;
class ObjectMotionState;

class PhysicalObject {
private:
    btRigidBody *m_body;
    ObjectMotionState *m_motionState;
public:
    PhysicalObject(btRigidBody *body);

    btRigidBody *body() const { return m_body; }

    void addFeedback(boost::shared_ptr<ObjectFeedback> feedback);

    void moveTo(Math::Vector location);
};

}  // namespace Physics
}  // namespace Kriti

#endif
