#ifndef KRITI_RENDER__RENDERABLE_H
#define KRITI_RENDER__RENDERABLE_H

#include <vector>

#include "Mesh.h"
#include "math/Vector.h"
#include "math/Quaternion.h"

namespace Kriti {
namespace Render {

class Renderable {
private:
    std::vector<Mesh *> m_meshes;
    Math::Vector m_location;
    Math::Quaternion m_orientation;
public:
    Renderable();
    ~Renderable();

    void addMesh(Mesh *mesh);
    int meshCount() const { return m_meshes.size(); }
    Mesh *mesh(int i) const { return m_meshes[i]; }

    Math::Vector &location() { return m_location; }
    Math::Quaternion &orientation() { return m_orientation; }
};

}  // namespace Render
}  // namespace Kriti

#endif
