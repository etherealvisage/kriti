#include <GL/glew.h>

#include "Technique.h"
#include "config/Tree.h"
#include "ResourceRegistry.h"

namespace Kriti {
namespace Render {

Technique::Technique() {

}

bool Technique::loadFrom(std::string identifier) {
    if(identifier == "") return false;
    boost::shared_ptr<Config::Tree> tree = Config::Tree::instance();

    std::string tbase = "techniques." + identifier;

    m_vertexShaderName = tree->getString(tbase + ".vertex_shader", "");
    if(m_vertexShaderName == "") {
        Message3(Render, Error, "Vertex shader not specified for technique \""
            << identifier << "\"");
        return false;
    }
    m_vertexShader = ResourceRegistry::instance()->get<Shader>(
        m_vertexShaderName + ".vert");
    if(!m_vertexShader) {
        Message3(Render, Error, "Could not find vertex shader \""
            << m_vertexShaderName << "\"");
        return false;
    }

    m_fragShaderName = tree->getString(tbase + ".frag_shader", "");
    if(m_fragShaderName == "") {
        Message3(Render, Error, "Frag shader not specified for technique \""
            << identifier << "\"");
        return false;
    }
    m_fragShader = ResourceRegistry::instance()->get<Shader>(
        m_fragShaderName + ".frag");
    if(!m_fragShader) {
        Message3(Render, Error, "Could not find frag shader \""
            << m_vertexShaderName << "\"");
        return false;
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShader->shaderID());
    glAttachShader(m_programID, m_fragShader->shaderID());

    glLinkProgram(m_programID);
    GLint status;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        Message3(Render, Error, "Shader linking failed for technique \""
            << identifier << "\":");
        char infoLog[4096];
        int used;
        glGetProgramInfoLog(m_programID, sizeof(infoLog), &used, infoLog);
        Message3(Render, Error, infoLog);
        return false;
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
