#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"
#include "ObjectFeedback.h"
#include "ObjectMotionState.h"
#include "Util.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

PhysicalObject::PhysicalObject(btRigidBody *body) : m_body(body) {
    if(body == NULL) {
        Message3(Physics, Fatal,
            "Constructing PhysicalObject from NULL btRigidBody!");
    }

    
    m_motionState = new ObjectMotionState();
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    // this may be dangerous.
    delete m_body->getMotionState();
    m_body->setMotionState(m_motionState);
    m_body->getMotionState()->setWorldTransform(current);
}

void PhysicalObject::addFeedback(boost::shared_ptr<ObjectFeedback> feedback) {
    m_motionState->addFeedback(feedback);
}

void PhysicalObject::moveTo(Math::Vector location) {
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    m_body->translate(toBullet(location) - current.getOrigin());
}

}  // namespace Physics
}  // namespace Kriti
