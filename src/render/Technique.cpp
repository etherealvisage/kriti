#include <GL/glew.h>

#include "Technique.h"
#include "TextureContext.h"

#include "config/Tree.h"

#include "ResourceRegistry.h"

namespace Kriti {
namespace Render {

bool Technique::loadFrom(std::string identifier) {
    if(identifier == "") return false;
    m_name = identifier;
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

void Technique::setUniform(const std::string &name,
    const Math::Matrix &matrix) {


    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniformMatrix4fv(location, 1, false, matrix.matrixData());
    }
}

void Technique::setUniform(const std::string &name, int value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniform1i(location, value);
    }
}

void Technique::setUniform(const std::string &name, float value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniform1f(location, value);
    }
}

void Technique::setUniform(const std::string &name,
    boost::shared_ptr<Texture> texture) {

    GLint location = getUniformLocation(name);
    if(location != -1) {
        int index = m_textureContext->bind(texture);
        glUniform1i(location, index);
    }
}

void Technique::activate(boost::shared_ptr<TextureContext> textureContext) {
    if(m_programID == 0) {
        Message3(Render, Error, "Activating non-loaded Technique . . .");
    }
    glUseProgram(m_programID);
    m_textureContext = textureContext;
    m_textureContext->nextTechnique();
}

GLint Technique::getUniformLocation(const std::string &name) {
    if(m_programID == 0) {
        Message3(Render, Error,
            "Getting uniform location for non-loaded technique!");

        return -1;
    }
    auto fi = m_uniformLocations.find(name);
    if(fi != m_uniformLocations.end()) return fi->second;

    GLint location = glGetUniformLocation(m_programID, name.c_str());
    m_uniformLocations[name] = location;

    if(location == -1) Message3(Render, Debug, "Unknown uniform " << name
        << " in technique " << m_name);

    return location;
}

}  // namespace Render
}  // namespace Kriti
