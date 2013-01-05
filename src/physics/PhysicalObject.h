#ifndef KRITI_PHYSICS__PHYSICAL_OBJECT_H
#define KRITI_PHYSICS__PHYSICAL_OBJECT_H

#include <boost/shared_ptr.hpp>

#include "math/Vector.h"
#include "math/Quaternion.h"

class btRigidBody;

namespace Kriti {
namespace Physics {

class ObjectFeedback;

class PhysicalObject {
private:
    btRigidBody *m_body;
    boost::shared_ptr<ObjectFeedback> m_feedback;
public:
    PhysicalObject(btRigidBody *body);

    btRigidBody *body() const { return m_body; }

    void setFeedback(boost::shared_ptr<ObjectFeedback> feedback);

    void moveTo(Math::Vector location);
};

}  // namespace Physics
}  // namespace Kriti

#endif
