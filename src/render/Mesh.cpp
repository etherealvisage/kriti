#include "Mesh.h"

namespace Kriti {
namespace Render {

VBO *Mesh::vertexVBO() {
    if(!m_vertexVBO) makeVBOs();
    return m_vertexVBO;
}

VBO *Mesh::normalVBO() {
    if(!m_normalVBO) makeVBOs();
    return m_normalVBO;
}

VBO *Mesh::texCoordVBO(int which) {
    if(!m_texCoordVBOs[which]) makeVBOs();
    return m_texCoordVBOs[which];
}

void Mesh::makeVBOs() {
    m_vertexVBO = new VBO();
    m_vertexVBO->setData(m_vertices);
    m_normalVBO = new VBO();
    m_normalVBO->setData(m_normals);

    for(auto &v : m_texCoords) {
        VBO *vbo = new VBO();
        vbo->setData2(v);
        m_texCoordVBOs.push_back(vbo);
    }
}

}  // namespace Render
}  // namespace Kriti
