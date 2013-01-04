#ifndef KRITI_PHYSICS__OBJECT_MANIPULATOR_H
#define KRITI_PHYSICS__OBJECT_MANIPULATOR_H

#include <boost/shared_ptr.hpp>

#include <BulletDynamics/Dynamics/btActionInterface.h>

#include "PhysicalObject.h"

namespace Kriti {
namespace Physics {

class ObjectManipulator : public btActionInterface {
private:
    boost::shared_ptr<PhysicalObject> m_object;
    Math::Vector m_linearForce;
public:
    ObjectManipulator(boost::shared_ptr<PhysicalObject> object);

    Math::Vector linearForce() const { return m_linearForce; }
    void setLinearForce(Math::Vector force) { m_linearForce = force; }

    // overloaded functions
    virtual void updateAction(btCollisionWorld *collisionWorld, btScalar step);
    virtual void debugDraw(btIDebugDraw *debugDrawer) {}
};

}  // namespace Physics
}  // namespace Kriti

#endif
