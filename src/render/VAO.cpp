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

void VAO::addVBO(boost::shared_ptr<VBO> vbo) {
    glBindVertexArray(m_arrayID);
    vbo->bindVBO();
    glBindVertexArray(0);
    m_elementVBO = vbo;
}

void VAO::addVBO(boost::shared_ptr<VBO> vbo, int location) {
    glBindVertexArray(m_arrayID);
    vbo->bindVBO(location);
    glBindVertexArray(0);
    m_dataVBOs.push_back(vbo);
}

void VAO::bind() {
    glBindVertexArray(m_arrayID);
}

}  // namespace Render
}  // namespace Kriti
