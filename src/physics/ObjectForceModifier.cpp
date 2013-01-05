#include "ObjectForceModifier.h"

#include "Util.h"

namespace Kriti {
namespace Physics {

void ObjectForceModifier::modify(boost::shared_ptr<World> world,
    btScalar step) {
    
    for(auto p : m_linearForce) {
        p.first->body()->applyCentralForce(toBullet(p.second * step));
    }
}

}  // namespace Physics
}  // namespace Kriti
