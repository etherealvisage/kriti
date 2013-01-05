#include "WorldRegistry.h"

namespace Kriti {
namespace Physics {

boost::shared_ptr<WorldRegistry> WorldRegistry::s_singleton;

WorldRegistry::WorldRegistry() {

}

boost::shared_ptr<World> WorldRegistry::makeWorld() {
    auto w = boost::make_shared<World>(Math::Vector(0.0, -1.0, 0.0));
    m_worlds.push_back(w);
    return w;
}

boost::shared_ptr<World> WorldRegistry::world(btDynamicsWorld *world) {
    for(auto w : m_worlds) {
        if(w->isWrapperFor(world)) return w;
    }
    return boost::shared_ptr<World>();
}

}  // namespace Physics
}  // namespace Kriti
