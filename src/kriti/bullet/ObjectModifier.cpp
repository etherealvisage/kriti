#include "ObjectModifier.h"

#include "WorldRegistry.h"

namespace Kriti {
namespace Bullet {

void ObjectModifier::updateAction(btCollisionWorld *collisionWorld,
    btScalar step) {
    
    auto world = WorldRegistry::get()->world(
        dynamic_cast<btDynamicsWorld *>(collisionWorld));
    if(world) modify(world, step);
}

}  // namespace Bullet
}  // namespace Kriti
