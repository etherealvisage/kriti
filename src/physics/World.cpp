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

void World::addModifier(boost::shared_ptr<ObjectModifier> modifier) {
    m_modifiers.push_back(modifier);
    m_world->addAction(modifier.get());
}

void World::step(TimeValue interval) {
    // step the requisite number of times @100Hz
    m_world->stepSimulation(interval.toUsec() / 1000.0, 10, 1 / 100.0);
}

}  // namespace Physics
}  // namespace Kriti
