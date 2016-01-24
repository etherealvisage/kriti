#include "../ogl.h"

#include "Program.h"
#include "TextureContext.h"
#include "ErrorTracker.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"

#include "../math/Vector.h"

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

    ErrorTracker::trackFrom("Program constructor (before all)");
    m_programID = gl::CreateProgram();
    ErrorTracker::trackFrom("Program constructor (after program creation)");
    gl::AttachShader(m_programID, m_vertexShader->shaderID());
    ErrorTracker::trackFrom("Program constructor (after vertex attachement)");
    gl::AttachShader(m_programID, m_fragShader->shaderID());
    ErrorTracker::trackFrom("Program constructor (after frag attachement)");
    if(m_geomShader) {
        gl::AttachShader(m_programID, m_geomShader->shaderID());
    }
    ErrorTracker::trackFrom("Program constructor (after geom attachement)");

    gl::LinkProgram(m_programID);
    ErrorTracker::trackFrom("Program constructor (after link)");
    GLint status;
    gl::GetProgramiv(m_programID, gl::LINK_STATUS, &status);
    if(status == gl::FALSE_) {
        Message3(Render, Error, "Shader linking failed for program with "
            "vertex shader " << vsName << " fragment shader " << fsName
            << " and geom shader " << gsName);
        char infoLog[4096];
        int used;
        gl::GetProgramInfoLog(m_programID, sizeof(infoLog), &used, infoLog);
        ErrorTracker::trackFrom("Program constructor (after get link log)");
        Message3(Render, Fatal, infoLog);
    }
}

void Program::setUniform(const std::string &name, const Math::Vector &value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        gl::Uniform3f(location, value.x(), value.y(), value.z());
        ErrorTracker::trackFrom("Program set uniform (after vector set)");
    }
}

void Program::setUniform(const std::string &name,
    const Math::Matrix &matrix) {


    GLint location = getUniformLocation(name);
    if(location != -1) {
        gl::UniformMatrix4fv(location, 1, false, matrix.matrixData());
        ErrorTracker::trackFrom("Program set uniform (after matrix set)");
    }
}

void Program::setUniform(const std::string &name, int value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        gl::Uniform1i(location, value);
        ErrorTracker::trackFrom("Program set uniform (after integer set)");
    }
}

void Program::setUniform(const std::string &name, float value) {
    GLint location = getUniformLocation(name);
    if(location != -1) {
        gl::Uniform1f(location, value);
        ErrorTracker::trackFrom("Program set uniform (after float set)");
    }
}

void Program::setUniform(const std::string &name,
    boost::shared_ptr<Texture> texture) {

    GLint location = getUniformLocation(name);
    if(location != -1) {
        int index = TextureContext::instance()->bind(texture);
        gl::Uniform1i(location, index);
        ErrorTracker::trackFrom("Program set uniform (after texture set)");
    }
}

void Program::activate() {
    if(m_programID == 0) {
        Message3(Render, Error, "Activating non-loaded Program . . .");
    }
    ErrorTracker::trackFrom("Program activate (before all)");
    gl::UseProgram(m_programID);
    ErrorTracker::trackFrom("Program activate (after activation)");
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

    ErrorTracker::trackFrom("Program uniform location (before all)");
    GLint location = gl::GetUniformLocation(m_programID, name.c_str());
    ErrorTracker::trackFrom("Program uniform location (after get)");
    m_uniformLocations[name] = location;

    if(location == -1) Message3(Render, Debug, "Unknown uniform " << name
        << " with program " << m_vsName << "/" << m_fsName);

    return location;
}

}  // namespace Render
}  // namespace Kriti
