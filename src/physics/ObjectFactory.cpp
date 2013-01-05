#include <boost/make_shared.hpp>

#include <btBulletDynamicsCommon.h>

#include "ObjectFactory.h"
#include "Util.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

boost::shared_ptr<PhysicalObject> ObjectFactory::makeSphere(double mass,
    double radius) {

    btCollisionShape *shape = new btSphereShape(radius);

    return fromShape(mass, shape);
}

boost::shared_ptr<PhysicalObject> ObjectFactory::makeIndexedTriMesh(
    double mass, const std::vector<Math::Vector> &vertices,
    const std::vector<unsigned int> &indices) {

    btTriangleMesh *triMesh = new btTriangleMesh();

    for(unsigned i = 0; i < indices.size(); i += 3) {
        triMesh->addTriangle(toBullet(vertices[indices[i]]),
            toBullet(vertices[indices[i+1]]),
            toBullet(vertices[indices[i+2]]));
    }
    //Message3(Physics, Debug, "triMesh size: " << triMesh->getNumTriangles());

    btCollisionShape *shape = new btBvhTriangleMeshShape(triMesh, true);

    return fromShape(mass, shape);
}

boost::shared_ptr<PhysicalObject> ObjectFactory::fromShape(
    double mass, btCollisionShape *shape) {

    btDefaultMotionState *ms = 
        new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
            btVector3(0,0,0)));

    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody *body = new btRigidBody(
        btRigidBody::btRigidBodyConstructionInfo(mass, ms, shape, inertia));

    body->setSleepingThresholds(0,0);

    return boost::make_shared<PhysicalObject>(body);
}

}  // namespace Physics
}  // namespace Kriti
