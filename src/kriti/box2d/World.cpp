#include "World.h"

#include <Box2D/Box2D.h>

namespace Kriti {
namespace Box2D {

World::World() {
    m_world = new b2World(b2Vec2(0.0f,0.0f));
}

}  // namespace Box2D
}  // namespace Kriti
