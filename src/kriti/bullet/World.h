#ifndef KRITI_BULLET__WORLD_H
#define KRITI_BULLET__WORLD_H

#include <map>

#include <btBulletDynamicsCommon.h>

#include <boost/shared_ptr.hpp>

#include "PhysicalObject.h"
#include "ObjectModifier.h"

#include "../math/Vector.h"

#include "../TimeValue.h"

namespace Kriti {
namespace Bullet {

class World {
private:
    boost::shared_ptr<btBroadphaseInterface> m_bpInterface;
    boost::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfig;
    boost::shared_ptr<btCollisionDispatcher> m_collisionDispatcher;
    boost::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
    boost::shared_ptr<btDiscreteDynamicsWorld> m_world;

    std::map<const btRigidBody *, boost::shared_ptr<PhysicalObject>>
        m_objectMap;
    std::vector<boost::shared_ptr<PhysicalObject>> m_objects;
    std::vector<boost::shared_ptr<ObjectModifier>> m_modifiers;
public:
    World(Math::Vector gravity);
    ~World();

    bool isWrapperFor(btDynamicsWorld *world) const
        { return m_world.get() == world; }

    void addObject(boost::shared_ptr<PhysicalObject> object);
    void addModifier(boost::shared_ptr<ObjectModifier> modifier);

    void step(TimeValue interval);

    boost::shared_ptr<PhysicalObject> rayCast(Math::Vector from,
        Math::Vector to, double *distance,
        boost::shared_ptr<PhysicalObject> ignore
            = boost::shared_ptr<PhysicalObject>());
};

}  // namespace Bullet
}  // namespace Kriti

#endif
