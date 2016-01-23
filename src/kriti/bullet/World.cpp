#include "World.h"

#include "Util.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Bullet {

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
    m_objects.push_back(object);
    m_objectMap[object->body()] = object;
    m_world->addRigidBody(object->body());
}

void World::addModifier(boost::shared_ptr<ObjectModifier> modifier) {
    m_modifiers.push_back(modifier);
    m_world->addAction(modifier.get());
}

void World::step(TimeValue interval) {
    // step the requisite number of times @100Hz
    //Message3(Bullet, Debug, "Bullet tick length: " << interval.toUsec() / 1e6);
    m_world->stepSimulation(interval.toUsec() / 1e3, 2, 1 / 60.0);
}

boost::shared_ptr<PhysicalObject> World::rayCast(Math::Vector from,
    Math::Vector to, double *distance,
    boost::shared_ptr<PhysicalObject> ignore) {

    auto bfrom = toBullet(from), bto = toBullet(to);
    btCollisionWorld::ClosestRayResultCallback callback(bfrom, bto);
    m_world->rayTest(bfrom, bto, callback);

    if(callback.hasHit()) {
        *distance = toMath(callback.m_hitPointWorld
            - callback.m_rayFromWorld).length();

        return boost::shared_ptr<PhysicalObject>(
            m_objectMap[dynamic_cast<const btRigidBody *>(
                callback.m_collisionObject)]);
    }
    else return boost::shared_ptr<PhysicalObject>();
}

}  // namespace Bullet
}  // namespace Kriti
