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
    Math::Vector linearVelocity() const;
    // ObjectFeedback should be used instead of these.
    Math::Vector position() const;
    Math::Quaternion orientation() const;

    void addFeedback(boost::shared_ptr<ObjectFeedback> feedback);

    void applyForce(Math::Vector force);
    void applyForce(Math::Vector from, Math::Vector force);
    void applyTorque(Math::Vector torque);
    void moveTo(Math::Vector location);

    void setLinearDamping(double damping);
    void setAngularDamping(double damping);
};

}  // namespace Physics
}  // namespace Kriti

#endif
