#ifndef KRITI_PHYSICS__OBJECT_MODIFIER_H
#define KRITI_PHYSICS__OBJECT_MODIFIER_H

#include <boost/shared_ptr.hpp>

#include <BulletDynamics/Dynamics/btActionInterface.h>

namespace Kriti {
namespace Physics {

class World;

class ObjectModifier : public btActionInterface {
public:
    virtual ~ObjectModifier() {}

    virtual void updateAction(btCollisionWorld *collisionWorld, btScalar step);
    virtual void debugDraw(btIDebugDraw *) {}
protected:
    virtual void modify(boost::shared_ptr<World> world, btScalar step) = 0;
};

}  // namespace Physics
}  // namespace Kriti

#endif
