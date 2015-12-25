#include <GL/glew.h>
#include <boost/algorithm/string/predicate.hpp>

#include "Shader.h"
#include "ErrorTracker.h"

#include "../ResourceRegistry.h"
#include "../FileResource.h"

namespace Kriti {
namespace Render {

Shader::Shader() {

}

Shader::~Shader() {

}

bool Shader::loadFrom(std::string identifier) {
    boost::shared_ptr<FileResource> shaderFile
        = ResourceRegistry::get<FileResource>("shaders/" + identifier);
    // Determine what type of shader this is.
    bool isVertex = boost::algorithm::ends_with(identifier, ".vert");
    bool isFrag = boost::algorithm::ends_with(identifier, ".frag");
    bool isGeom = boost::algorithm::ends_with(identifier, ".geom");
    if(!isVertex && !isFrag && !isGeom) {
        Message3(Render, Error, "Not sure what to do with shader \"" 
            << identifier << "\": neither vertex, fragment, nor geom shader.");
        return false;
    }

    ErrorTracker::trackFrom("Shader loading (before all)");
    if(isVertex) m_shaderID = glCreateShader(GL_VERTEX_SHADER);
    if(isFrag) m_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if(isGeom) m_shaderID = glCreateShader(GL_GEOMETRY_SHADER);
    ErrorTracker::trackFrom("Shader loading (after create)");

    std::string content = shaderFile->fileContent();
    const char *cptr = content.c_str();

    glShaderSource(m_shaderID, 1, &cptr, NULL);
    ErrorTracker::trackFrom("Shader loading (after source spec)");

    glCompileShader(m_shaderID);
    ErrorTracker::trackFrom("Shader loading (after compliation)");

    GLint status;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        Message3(Render, Error, "Failed to compile shader \"" <<
            identifier << "\":");
        char infoLog[4096];
        int used;
        glGetShaderInfoLog(m_shaderID, sizeof(infoLog), &used, infoLog);
        ErrorTracker::trackFrom("Shader loading (after get compile log)");
        Message3(Render, Error, infoLog);
        return false;
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
