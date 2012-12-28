#include <btBulletDynamicsCommon.h>

#include "BulletWrapper.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

boost::shared_ptr<BulletWrapper> BulletWrapper::s_singleton;

BulletWrapper::BulletWrapper() {
    Message3(Physics, Log, "Initializing bullet . . .");
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

    m_world->setGravity(btVector3(0.0, -1.0, 0.0));
}

BulletWrapper::~BulletWrapper() {
    Message3(Physics, Log, "Destroying bullet . . .");
}

void BulletWrapper::stepWorld(int usec) {
    m_world->stepSimulation(usec / 1000.0, 10, 1 / 100.0);
}

}  // namespace Physics
}  // namespace Kriti
