#include "../ogl.h"

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
    if(isVertex) m_shaderID = gl::CreateShader(gl::VERTEX_SHADER);
    if(isFrag) m_shaderID = gl::CreateShader(gl::FRAGMENT_SHADER);
    if(isGeom) {
        Message3(Render, Debug, "Kriti operating in GL3.1 mode.");
        Message3(Render, Fatal, "Geometry shader loading disabled.");
        //m_shaderID = gl::CreateShader(gl::GEOMETRY_SHADER);
    }
    ErrorTracker::trackFrom("Shader loading (after create)");

    std::string content = shaderFile->fileContent();
    const char *cptr = content.c_str();

    gl::ShaderSource(m_shaderID, 1, &cptr, NULL);
    ErrorTracker::trackFrom("Shader loading (after source spec)");

    gl::CompileShader(m_shaderID);
    ErrorTracker::trackFrom("Shader loading (after compliation)");

    GLint status;
    gl::GetShaderiv(m_shaderID, gl::COMPILE_STATUS, &status);
    if(status != gl::TRUE_) {
        Message3(Render, Error, "Failed to compile shader \"" <<
            identifier << "\":");
        char infoLog[4096];
        int used;
        gl::GetShaderInfoLog(m_shaderID, sizeof(infoLog), &used, infoLog);
        ErrorTracker::trackFrom("Shader loading (after get compile log)");
        Message3(Render, Error, infoLog);
        return false;
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
