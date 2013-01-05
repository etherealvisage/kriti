#ifndef KRITI_PHYSICS__OBJECT_FORCE_MODIFIER_H
#define KRITI_PHYSICS__OBJECT_FORCE_MODIFIER_H

#include <map>

#include "ObjectModifier.h"
#include "PhysicalObject.h"

#include "math/Vector.h"

namespace Kriti {
namespace Physics {

class ObjectForceModifier : public ObjectModifier {
private:
    std::map<boost::shared_ptr<PhysicalObject>, Math::Vector> m_linearForce;
public:
    virtual ~ObjectForceModifier() {}

    void setLinearForce(boost::shared_ptr<PhysicalObject> object,
        Math::Vector force) { m_linearForce[object] = force; }
protected:
    virtual void modify(boost::shared_ptr<World> world, btScalar step);
};

}  // namespace Physics
}  // namespace Kriti

#endif
