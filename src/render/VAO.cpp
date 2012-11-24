#include <GL/glew.h>

#include "VAO.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

VAO::VAO() : m_arrayID(0), m_mesh(NULL) {
    
}

void VAO::wrap(Mesh *mesh) {
    m_mesh = mesh;

    glGenVertexArrays(1, &m_arrayID);
    glBindVertexArray(m_arrayID);

    VBO *vertex = mesh->vertexVBO();
    vertex->bindVBO(0);
    VBO *normal = mesh->normalVBO();
    normal->bindVBO(1);

    for(int i = 0; i < mesh->texCoordCount(); i ++) {
        VBO *texture = mesh->texCoordVBO(i);
        texture->bindVBO(i + 2);
    }
}

void VAO::bind() {
    if(m_mesh == NULL || m_arrayID == 0) {
        Message3(Render, Error, "Trying to bind unwrapped VAO object.");
        return;
    }

    glBindVertexArray(m_arrayID);
}

}  // namespace Render
}  // namespace Kriti
