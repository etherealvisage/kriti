#include "ObjectManipulator.h"

#include "Util.h"

namespace Kriti {
namespace Physics {

ObjectManipulator::ObjectManipulator(
    boost::shared_ptr<PhysicalObject> object) : m_object(object) {

}


void ObjectManipulator::updateAction(btCollisionWorld *collisionWorld,
    btScalar step) {

    m_object->body()->applyCentralForce(toBullet(m_linearForce));
}

}  // namespace Physics
}  // namespace Kriti
