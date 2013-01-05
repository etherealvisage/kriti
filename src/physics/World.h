#ifndef KRITI_PHYSICS__WORLD_H
#define KRITI_PHYSICS__WORLD_H

#include <btBulletDynamicsCommon.h>

#include <boost/shared_ptr.hpp>

#include "PhysicalObject.h"

#include "math/Vector.h"

namespace Kriti {
namespace Physics {

class World {
private:
    boost::shared_ptr<btBroadphaseInterface> m_bpInterface;
    boost::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfig;
    boost::shared_ptr<btCollisionDispatcher> m_collisionDispatcher;
    boost::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
    boost::shared_ptr<btDiscreteDynamicsWorld> m_world;
public:
    World(Math::Vector gravity);
    ~World();

    bool isWrapperFor(btDynamicsWorld *world) const
        { return m_world.get() == world; }

    void addObject(boost::shared_ptr<PhysicalObject> object);
};

}  // namespace Physics
}  // namespace Kriti

#endif
