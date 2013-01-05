#ifndef KRITI_PHYSICS__PHYSICAL_OBJECT_H
#define KRITI_PHYSICS__PHYSICAL_OBJECT_H

#include <boost/shared_ptr.hpp>

class btRigidBody;

namespace Kriti {
namespace Physics {

class PhysicalObject {
private:
    btRigidBody *m_body;
public:
    PhysicalObject(btRigidBody *body);

    btRigidBody *body() const { return m_body; }
};

}  // namespace Physics
}  // namespace Kriti

#endif
