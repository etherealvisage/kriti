#include <GL/glew.h>

#include "Uniforms.h"
#include "Texture.h"
#include "Program.h"

namespace Kriti {
namespace Render {

void Uniforms::setParam(std::string name, int value) {
    m_ints[name] = value;
}

void Uniforms::setParam(std::string name, float value) {
    m_floats[name] = value;
}

void Uniforms::setParam(std::string name, const Math::Vector &vector) {
    m_vectors[name] = vector;
}

void Uniforms::setParam(std::string name, const Math::Matrix &matrix) {
    m_matrices[name] = matrix;
}

void Uniforms::setParam(std::string name, boost::shared_ptr<Texture> texture) {
    m_textures[name] = texture;
}

void Uniforms::set(boost::shared_ptr<Program> program) const {
    for(auto &i : m_ints) {
        program->setUniform(i.first, i.second);
    }

    for(auto &i : m_floats) {
        program->setUniform(i.first, i.second);
    }

    for(auto &v : m_vectors) {
        program->setUniform(v.first, v.second);
    }

    for(auto &m : m_matrices) {
        program->setUniform(m.first, m.second);
    }

    for(auto &t : m_textures) {
        program->setUniform(t.first, t.second);
    }
}
}  // namespace Render
}  // namespace Kriti
