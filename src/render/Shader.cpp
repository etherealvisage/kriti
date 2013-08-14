#include <GL/glew.h>
#include <boost/algorithm/string/predicate.hpp>

#include "Shader.h"

#include "ResourceRegistry.h"
#include "FileResource.h"

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
    if(!isVertex && !isFrag) {
        Message3(Render, Error, "Not sure what to do with shader \"" 
            << identifier << "\": neither vertex nor fragment shader.");
        return false;
    }

    m_shaderID = glCreateShader(isVertex?GL_VERTEX_SHADER:GL_FRAGMENT_SHADER);

    std::string content = shaderFile->fileContent();
    const char *cptr = content.c_str();

    glShaderSource(m_shaderID, 1, &cptr, NULL);

    glCompileShader(m_shaderID);

    GLint status;
    glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        Message3(Render, Error, "Failed to compile shader \"" <<
            identifier << "\":");
        char infoLog[4096];
        int used;
        glGetShaderInfoLog(m_shaderID, sizeof(infoLog), &used, infoLog);
        Message3(Render, Error, infoLog);
        return false;
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
