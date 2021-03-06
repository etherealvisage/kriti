#include "../ogl.h"

#include "VAO.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

VAO::VAO() : m_arrayID(0) {
    ErrorTracker::trackFrom("VAO constructor (before all)");
    gl::GenVertexArrays(1, &m_arrayID);
    ErrorTracker::trackFrom("VAO constructor (after gen)");
}

VAO::~VAO() {
    ErrorTracker::trackFrom("VAO destructor (before all)");
    gl::DeleteVertexArrays(1, &m_arrayID);
    ErrorTracker::trackFrom("VAO destructor (after delete)");
}

void VAO::addVBO(boost::shared_ptr<VBO> vbo, Location where) {
    ErrorTracker::trackFrom("VAO VBO addition (before all)");
    gl::BindVertexArray(m_arrayID);
    ErrorTracker::trackFrom("VAO VBO addition (after VAO bind)");
    if(where != Element) {
        vbo->bindVBO(where);
    }
    else {
        vbo->bindVBO();
    }
    gl::BindVertexArray(0);
    ErrorTracker::trackFrom("VAO VBO addition (after VAO clear)");
    m_vbos[where] = vbo;
}

void VAO::bind() {
    ErrorTracker::trackFrom("VAO bind (before all)");
    gl::BindVertexArray(m_arrayID);
    ErrorTracker::trackFrom("VAO bind (after bind)");
}

}  // namespace Render
}  // namespace Kriti
