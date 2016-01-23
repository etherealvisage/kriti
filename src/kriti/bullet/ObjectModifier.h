#ifndef KRITI_BULLET__OBJECT_MODIFIER_H
#define KRITI_BULLET__OBJECT_MODIFIER_H

#include <boost/shared_ptr.hpp>

#include <BulletDynamics/Dynamics/btActionInterface.h>

namespace Kriti {
namespace Bullet {

class World;

class ObjectModifier : public btActionInterface {
public:
    virtual ~ObjectModifier() {}

    virtual void updateAction(btCollisionWorld *collisionWorld, btScalar step);
    virtual void debugDraw(btIDebugDraw *) {}
protected:
    virtual void modify(boost::shared_ptr<World> world, btScalar step) = 0;
};

}  // namespace Bullet
}  // namespace Kriti

#endif
