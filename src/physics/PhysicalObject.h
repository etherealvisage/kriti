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
    Math::Vector m_linearForce;
private:
    PhysicalObject(btRigidBody *body);
public:
    static PhysicalObject *fromSphere(double radius, double mass);

    static PhysicalObject *fromModel(boost::shared_ptr<Render::Model> model,
        double mass);

    static PhysicalObject *fromTriGeometry(double mass,
        const std::vector<Math::Vector> &vertices,
        const std::vector<unsigned int> &indices);

    btRigidBody *body() const { return m_body; }

    Math::Vector linearForce() const { return m_linearForce; }
    void setLinearForce(Math::Vector force) { m_linearForce = force; }

    void setLocation(Math::Vector location);
    void setOrientation(Math::Quaternion orientation);
    Math::Vector location() const;
    Math::Quaternion orientation() const;
};

}  // namespace Physics
}  // namespace Kriti

#endif
