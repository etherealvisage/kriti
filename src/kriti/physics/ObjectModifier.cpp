#include "ObjectModifier.h"

#include "WorldRegistry.h"

namespace Kriti {
namespace Physics {

void ObjectModifier::updateAction(btCollisionWorld *collisionWorld,
    btScalar step) {
    
    auto world = WorldRegistry::instance()->world(
        dynamic_cast<btDynamicsWorld *>(collisionWorld));
    if(world) modify(world, step);
}

}  // namespace Physics
}  // namespace Kriti
