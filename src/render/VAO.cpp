#include <GL/glew.h>

#include "VAO.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Render {

VAO::VAO() : m_arrayID(0) {
    glGenVertexArrays(1, &m_arrayID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &m_arrayID);
}

void VAO::addVBO(boost::shared_ptr<VBO> vbo, Location where) {
    glBindVertexArray(m_arrayID);
    if(where != Element) {
        vbo->bindVBO(where);
    }
    else {
        vbo->bindVBO();
    }
    glBindVertexArray(0);
    m_vbos[where] = vbo;
}

void VAO::bind() {
    glBindVertexArray(m_arrayID);
}

}  // namespace Render
}  // namespace Kriti
