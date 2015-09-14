#include "ObjectForceModifier.h"
#include "World.h"
#include "Util.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Physics {

void ObjectForceModifier::modify(boost::shared_ptr<World> world,
    btScalar step) {

    if(!m_enabled) return;
    
    for(auto p : m_linearForce) {
        p.first->body()->applyCentralForce(toBullet(p.second));
    }
}

}  // namespace Physics
}  // namespace Kriti
