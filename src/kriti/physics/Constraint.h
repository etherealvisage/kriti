#ifndef KRITI_PHYSICS__CONSTRAINT_H
#define KRITI_PHYSICS__CONSTRAINT_H

#include <boost/shared_ptr.hpp>

#include "PhysicalObject.h"

namespace Kriti {
namespace Physics {

class Constraint {
private:
    boost::shared_ptr<PhysicalObject> m_objects[2];
public:
    Constraint(boost::shared_ptr<PhysicalObject> obj1,
        boost::shared_ptr<PhysicalObject> obj2);

    boost::shared_ptr<PhysicalObject> object(int which) const
        { return m_objects[which]; }
};

}  // namespace Physics
}  // namespace Kriti

#endif
