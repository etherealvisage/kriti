#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"
#include "ObjectFeedback.h"
#include "Util.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

PhysicalObject::PhysicalObject(btRigidBody *body) : m_body(body) {
    if(body == NULL) {
        Message3(Physics, Fatal,
            "Constructing PhysicalObject from NULL btRigidBody!");
    }
}

void PhysicalObject::setFeedback(boost::shared_ptr<ObjectFeedback> feedback) {
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    m_body->setMotionState(feedback.get());
    m_body->getMotionState()->setWorldTransform(current);
    m_feedback = feedback;
}

void PhysicalObject::moveTo(Math::Vector location) {
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    m_body->translate(toBullet(location) - current.getOrigin());
}

}  // namespace Physics
}  // namespace Kriti
