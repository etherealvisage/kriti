#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"
#include "BulletWrapper.h"
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

PhysicalObject *PhysicalObject::fromSphere(double radius, double mass) {
    btCollisionShape *sphereShape = new btSphereShape(radius);

    btDefaultMotionState *ms =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
            btVector3(0,0,0)));

    btVector3 initialInertia(0,0,0);
    sphereShape->calculateLocalInertia(mass, initialInertia);

    btRigidBody *rigidBody = new btRigidBody(
        btRigidBody::btRigidBodyConstructionInfo(mass, ms, sphereShape,
            initialInertia));

    BulletWrapper::instance()->world()->addRigidBody(rigidBody);

    return new PhysicalObject(rigidBody);
}

PhysicalObject *PhysicalObject::fromTriGeometry(double mass,
    const std::vector<Math::Vector> &vertices,
    const std::vector<unsigned int> &indices) {

    btTriangleMesh *mesh = new btTriangleMesh();

    for(unsigned i = 0; i < indices.size(); i += 3) {
        btVector3 v1(toBullet(vertices[indices[i]]));
        btVector3 v2(toBullet(vertices[indices[i+1]]));
        btVector3 v3(toBullet(vertices[indices[i+2]]));
        mesh->addTriangle(v1, v2, v3);
    }

    btCollisionShape *meshShape = new btBvhTriangleMeshShape(mesh, true);

    btDefaultMotionState *ms =
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
            btVector3(0,0,0)));

    btVector3 initialInertia(0,0,0);
    meshShape->calculateLocalInertia(mass, initialInertia);

    btRigidBody *rigidBody = new btRigidBody(
        btRigidBody::btRigidBodyConstructionInfo(mass, ms, meshShape,
            initialInertia));

    BulletWrapper::instance()->world()->addRigidBody(rigidBody);

    return new PhysicalObject(rigidBody);
}

void PhysicalObject::setLocation(Math::Vector location) {
    btTransform trans = m_body->getCenterOfMassTransform();
    trans.setOrigin(btVector3(location.x(), location.y(), location.z()));
    m_body->setCenterOfMassTransform(trans);
}

void PhysicalObject::setOrientation(Math::Quaternion orientation) {
    btTransform trans = m_body->getCenterOfMassTransform();
    Math::Vector axis;
    double angle;
    orientation.toAxisAngle(axis, angle);
    trans.setRotation(btQuaternion(btVector3(axis.x(), axis.y(), axis.z()),
        angle));
    m_body->setCenterOfMassTransform(trans);
}

Math::Vector PhysicalObject::location() const {
    btTransform trans;
    m_body->getMotionState()->getWorldTransform(trans);

    return Math::Vector(trans.getOrigin().getX(), trans.getOrigin().getY(),
        trans.getOrigin().getZ());
}

Math::Quaternion PhysicalObject::orientation() const {
    btTransform trans;
    m_body->getMotionState()->getWorldTransform(trans);

    btQuaternion quat = trans.getRotation();

    return Math::Quaternion(Math::Vector(quat.getAxis().getX(),
        quat.getAxis().getY(), quat.getAxis().getZ()), quat.getAngle());
}

}  // namespace Physics
}  // namespace Kriti
