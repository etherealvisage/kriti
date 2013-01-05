#include <btBulletDynamicsCommon.h>

#include "PhysicalObject.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Physics {

PhysicalObject::PhysicalObject(btRigidBody *body) : m_body(body) {
    if(body == NULL) {
        Message3(Physics, Fatal,
            "Constructing PhysicalObject from NULL btRigidBody!");
    }
}

}  // namespace Physics
}  // namespace Kriti
