#ifndef KRITI_PHYSICS__WORLD_REGISTRY_H
#define KRITI_PHYSICS__WORLD_REGISTRY_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "World.h" 

namespace Kriti {
namespace Physics {

class WorldRegistry {
private:
    static boost::shared_ptr<WorldRegistry> s_singleton;
public:
    static boost::shared_ptr<WorldRegistry> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<WorldRegistry>(
                new WorldRegistry());
        }
        return s_singleton;
    }

    static void destroy() {
        s_singleton.reset();
    }
private:
    std::vector<boost::shared_ptr<World>> m_worlds;
private:
    WorldRegistry();
public:
    boost::shared_ptr<World> makeWorld();
    boost::shared_ptr<World> world(btDynamicsWorld *world);
};

}  // namespace Physics
}  // namespace Kriti

#endif
