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

Math::Vector PhysicalObject::linearVelocity() const {
    return toMath(m_body->getLinearVelocity());
}

Math::Vector PhysicalObject::position() const {
    return toMath(m_body->getCenterOfMassTransform().getOrigin());
}

Math::Quaternion PhysicalObject::orientation() const {
    return toMath(m_body->getCenterOfMassTransform().getRotation());
}

void PhysicalObject::addFeedback(boost::shared_ptr<ObjectFeedback> feedback) {
    m_motionState->addFeedback(feedback);
}

void PhysicalObject::applyForce(Math::Vector force) {
    m_body->applyCentralForce(toBullet(force));
}

void PhysicalObject::applyForce(Math::Vector from, Math::Vector force) {
    m_body->applyForce(toBullet(force), toBullet(from));
}

void PhysicalObject::applyTorque(Math::Vector torque) {
    m_body->applyTorque(toBullet(torque));
}

void PhysicalObject::moveTo(Math::Vector location) {
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    m_body->translate(toBullet(location) - current.getOrigin());
}

void PhysicalObject::setOrientation(Math::Quaternion orientation) {
    btTransform current;
    m_body->getMotionState()->getWorldTransform(current);
    current.setRotation(toBullet(orientation));
    m_body->getMotionState()->setWorldTransform(current);
}

void PhysicalObject::setLinearDamping(double damping) {
    m_body->setDamping(damping, m_body->getAngularDamping());
}

void PhysicalObject::setAngularDamping(double damping) {
    m_body->setDamping(m_body->getLinearDamping(), damping);
}

}  // namespace Physics
}  // namespace Kriti
