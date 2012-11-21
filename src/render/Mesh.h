#ifndef KRITI_RENDER__MESH_H
#define KRITI_RENDER__MESH_H

#include "math/Vector.h"

#include "Material.h"
#include "Technique.h"
#include "TechniqueParams.h"

namespace Kriti {
namespace Render {

class Mesh {
private:
    std::vector<Math::Vector> m_vertices;
    std::vector<Math::Vector> m_normals;
    std::vector<std::vector<Math::Vector>> m_texCoords;
public:
    Mesh();
    ~Mesh();

    void setVertices(const std::vector<Math::Vector> &vertices);
    void setNormals(const std::vector<Math::Vector> &normals);
    void addTexCoords(const std::vector<Math::Vector> &texCoords);
};

}  // namespace Render
}  // namespace Kriti

#endif
