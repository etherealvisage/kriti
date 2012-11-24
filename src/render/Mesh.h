#ifndef KRITI_RENDER__MESH_H
#define KRITI_RENDER__MESH_H

#include "math/Vector.h"

#include "Material.h"
#include "Technique.h"
#include "TechniqueParams.h"
#include "VBO.h"

namespace Kriti {
namespace Render {

class Mesh {
private:
    std::vector<Math::Vector> m_vertices;
    std::vector<Math::Vector> m_normals;
    std::vector<std::vector<Math::Vector>> m_texCoords;
    VBO *m_vertexVBO;
    VBO *m_normalVBO;
    std::vector<VBO *> m_texCoordVBOs;
public:
    Mesh() {}
    ~Mesh() {}

    int texCoordCount() const { return m_texCoords.size(); }

    VBO *vertexVBO();
    VBO *normalVBO();
    VBO *texCoordVBO(int which);

    void setVertices(const std::vector<Math::Vector> &vertices);
    void setNormals(const std::vector<Math::Vector> &normals);
    void addTexCoords(const std::vector<Math::Vector> &texCoords);
private:
    void makeVBOs();
};

}  // namespace Render
}  // namespace Kriti

#endif
