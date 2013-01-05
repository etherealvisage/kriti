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
    bool m_enabled;
    std::map<boost::shared_ptr<PhysicalObject>, Math::Vector> m_linearForce;
public:
    ObjectForceModifier() : m_enabled(true) {}
    virtual ~ObjectForceModifier() {}

    void enable() { m_enabled = true; }
    void disable() { m_enabled = false; }
    void toggle() { m_enabled = !m_enabled; }
    bool isEnabled() const { return m_enabled; }

    void setLinearForce(boost::shared_ptr<PhysicalObject> object,
        Math::Vector force) { m_linearForce[object] = force; }
protected:
    virtual void modify(boost::shared_ptr<World> world, btScalar step);
};

}  // namespace Physics
}  // namespace Kriti

#endif
