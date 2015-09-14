#include <GL/glew.h>

#include "Program.h"
#include "TextureContext.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"

namespace Kriti {
namespace Render {

Program::Program(std::string vsName, std::string fsName, std::string gsName)
    : m_vsName(vsName), m_fsName(fsName), m_gsName(gsName) {

    m_vertexShader = ResourceRegistry::get<Shader>(vsName + ".vert");
    if(!m_vertexShader) {
        Message3(Render, Fatal, "Could not find vertex shader \""
            << vsName << "\"");
    }

    m_fragShader = ResourceRegistry::get<Shader>(fsName + ".frag");
    if(!m_fragShader) {
        Message3(Render, Fatal, "Could not find frag shader \""
            << fsName << "\"");
    }

    if(m_gsName != "") {
        m_geomShader = ResourceRegistry::get<Shader>(gsName + ".geom");
        if(!m_geomShader) {
            Message3(Render, Fatal, "Could not find geometry shader \""
                << gsName << "\"");
        }
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShader->shaderID());
    glAttachShader(m_programID, m_fragShader->shaderID());
    if(m_geomShader) glAttachShader(m_programID, m_geomShader->shaderID());

    glLinkProgram(m_programID);
    GLint status;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        Message3(Render, Error, "Shader linking failed for program with "
            "vertex shader " << vsName << " fragment shader " << fsName
            << " and geom shader " << gsName);
        char infoLog[4096];
        int used;
        glGetProgramInfoLog(m_programID, sizeof(infoLog), &used, infoLog);
        Message3(Render, Fatal, infoLog);
    }
}

void Program::setUniform(const std::string &name, const Math::Vector &value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniform3f(location, value.x(), value.y(), value.z());
    }
}

void Program::setUniform(const std::string &name,
    const Math::Matrix &matrix) {


    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniformMatrix4fv(location, 1, false, matrix.matrixData());
    }
}

void Program::setUniform(const std::string &name, int value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniform1i(location, value);
    }
}

void Program::setUniform(const std::string &name, float value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        glUniform1f(location, value);
    }
}

void Program::setUniform(const std::string &name,
    boost::shared_ptr<Texture> texture) {

    GLint location = getUniformLocation(name);
    if(location != -1) {
        int index = TextureContext::instance()->bind(texture);
        glUniform1i(location, index);
    }
}

void Program::activate() {
    if(m_programID == 0) {
        Message3(Render, Error, "Activating non-loaded Program . . .");
    }
    glUseProgram(m_programID);
    TextureContext::instance()->nextProgram();
}

GLint Program::getUniformLocation(const std::string &name) {
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
        << " with program " << m_vsName << "/" << m_fsName);

    return location;
}

}  // namespace Render
}  // namespace Kriti
