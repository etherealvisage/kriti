#include <GL/glew.h>

#include "VAO.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

VAO::VAO() : m_arrayID(0) {
    ErrorTracker::trackFrom("VAO constructor (before all)");
    glGenVertexArrays(1, &m_arrayID);
    ErrorTracker::trackFrom("VAO constructor (after gen)");
}

VAO::~VAO() {
    ErrorTracker::trackFrom("VAO destructor (before all)");
    glDeleteVertexArrays(1, &m_arrayID);
    ErrorTracker::trackFrom("VAO destructor (after delete)");
}

void VAO::addVBO(boost::shared_ptr<VBO> vbo, Location where) {
    ErrorTracker::trackFrom("VAO VBO addition (before all)");
    glBindVertexArray(m_arrayID);
    ErrorTracker::trackFrom("VAO VBO addition (after VAO bind)");
    if(where != Element) {
        vbo->bindVBO(where);
    }
    else {
        vbo->bindVBO();
    }
    glBindVertexArray(0);
    ErrorTracker::trackFrom("VAO VBO addition (after VAO clear)");
    m_vbos[where] = vbo;
}

void VAO::bind() {
    ErrorTracker::trackFrom("VAO bind (before all)");
    glBindVertexArray(m_arrayID);
    ErrorTracker::trackFrom("VAO bind (after bind)");
}

}  // namespace Render
}  // namespace Kriti
