#include "World.h"

#include "Util.h"

namespace Kriti {
namespace Physics {

World::World(Math::Vector gravity) {
    m_bpInterface = boost::shared_ptr<btBroadphaseInterface>(
        new btDbvtBroadphase());

    m_collisionConfig = boost::shared_ptr<btDefaultCollisionConfiguration>(
        new btDefaultCollisionConfiguration());

    m_collisionDispatcher = boost::shared_ptr<btCollisionDispatcher>(
        new btCollisionDispatcher(m_collisionConfig.get()));

    m_solver = boost::shared_ptr<btSequentialImpulseConstraintSolver>(
        new btSequentialImpulseConstraintSolver());

    m_world = boost::shared_ptr<btDiscreteDynamicsWorld>(
        new btDiscreteDynamicsWorld(m_collisionDispatcher.get(),
            m_bpInterface.get(), m_solver.get(), m_collisionConfig.get()));

    m_world->setGravity(toBullet(gravity));
}

World::~World() {

}

void World::addObject(boost::shared_ptr<PhysicalObject> object) {
    m_world->addRigidBody(object->body());
}

}  // namespace Physics
}  // namespace Kriti
