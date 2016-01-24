#ifndef KRITI_BOX2D__WORLD_H
#define KRITI_BOX2D__WORLD_H

struct b2World;

namespace Kriti {
namespace Box2D {

class World {
private:
    b2World *m_world;
public:
    World();
};

}  // namespace Box2D
}  // namespace Kriti

#endif
