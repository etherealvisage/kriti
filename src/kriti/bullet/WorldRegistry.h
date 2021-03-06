#ifndef KRITI_BULLET__WORLD_REGISTRY_H
#define KRITI_BULLET__WORLD_REGISTRY_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "World.h" 

#include "../Singleton.h"

namespace Kriti {
namespace Bullet {

class WorldRegistry : public Singleton<WorldRegistry> {
    friend class Singleton<WorldRegistry>;
private:
    std::vector<boost::shared_ptr<World>> m_worlds;
public:
    WorldRegistry();
    ~WorldRegistry() {}
public:
    boost::shared_ptr<World> makeWorld();
    boost::shared_ptr<World> world(btDynamicsWorld *world);
};

}  // namespace Bullet
}  // namespace Kriti

#endif
