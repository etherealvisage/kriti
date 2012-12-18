#ifndef KRITI_PHYSICS__PHYSICAL_OBJECT_H
#define KRITI_PHYSICS__PHYSICAL_OBJECT_H

#include <boost/shared_ptr.hpp>

#include "math/Vector.h"
#include "math/Quaternion.h"

#include "render/Model.h"

class btRigidBody;

namespace Kriti {
namespace Physics {

class PhysicalObject {
private:
    btRigidBody *m_body;
private:
    PhysicalObject(btRigidBody *body);
public:
    static PhysicalObject *fromSphere(double radius, double mass);

    static PhysicalObject *fromModel(boost::shared_ptr<Render::Model> model,
        double mass);

    void setLocation(Math::Vector location);
    void setOrientation(Math::Quaternion orientation);
    Math::Vector location() const;
    Math::Quaternion orientation() const;
};

}  // namespace Physics
}  // namespace Kriti

#endif
