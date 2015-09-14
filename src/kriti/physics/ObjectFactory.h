#ifndef KRITI_PHYSICS__OBJECT_FACTORY_H
#define KRITI_PHYSICS__OBJECT_FACTORY_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "PhysicalObject.h"

#include "../math/Vector.h"

class btCollisionShape;

namespace Kriti {
namespace Physics {

class ObjectFactory {
public:
    boost::shared_ptr<PhysicalObject> makeSphere(double mass, double radius);
    boost::shared_ptr<PhysicalObject> makeBox(double mass, double w, double h,
        double d);
    boost::shared_ptr<PhysicalObject> makeTriMesh(double mass,
        const std::vector<Math::Vector> &vertices);
    boost::shared_ptr<PhysicalObject> makeIndexedTriMesh(double mass,
        const std::vector<Math::Vector> &vertices,
        const std::vector<unsigned int> &indices);
private:
    boost::shared_ptr<PhysicalObject> fromShape(double mass,
        btCollisionShape *shape);
};

}  // namespace Physics
}  // namespace Kriti

#endif
