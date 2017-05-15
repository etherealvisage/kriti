#include "Uniforms.h"
#include "Texture.h"
#include "Program.h"

#include "../math/Vector.h"
#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

void Uniforms::setParam(const std::string &name, int value) {
    m_ints[name] = value;
}

int Uniforms::getInt(const std::string &name) const {
    auto it = m_ints.find(name);
    if(it != m_ints.end()) return it->second;

    Message3(Render, Error, "Couldn't get int with name \"" << name
        << "\" from uniforms");
    return 0;
}

void Uniforms::setParam(const std::string &name, float value) {
    m_floats[name] = value;
}

float Uniforms::getFloat(const std::string &name) const {
    auto it = m_floats.find(name);
    if(it != m_floats.end()) return it->second;

    Message3(Render, Error, "Couldn't get float with name \"" << name
        << "\" from uniforms");
    return 0;
}

void Uniforms::setParam(const std::string &name, const Math::Vector &vector) {
    m_vectors[name] = vector;
}

Math::Vector Uniforms::getVector(const std::string &name) const {
    auto it = m_vectors.find(name);
    if(it != m_vectors.end()) return it->second;

    Message3(Render, Error, "Couldn't get vector with name \"" << name
        << "\" from uniforms");
    return Math::Vector();
}

void Uniforms::setParam(const std::string &name, const Math::Colour &colour) {
    m_colours[name] = colour;
}

Math::Colour Uniforms::getColour(const std::string &name) const {
    auto it = m_colours.find(name);
    if(it != m_colours.end()) return it->second;

    Message3(Render, Error, "Couldn't get colour with name \"" << name
        << "\" from uniforms");
    return Math::Colour();
}

void Uniforms::setParam(const std::string &name, const Math::Matrix &matrix) {
    m_matrices[name] = matrix;
}

Math::Matrix Uniforms::getMatrix(const std::string &name) const {
    auto it = m_matrices.find(name);
    if(it != m_matrices.end()) return it->second;

    Message3(Render, Error, "Couldn't get matrix with name \"" << name
        << "\" from uniforms");
    return Math::Matrix();
}

void Uniforms::setParam(const std::string &name,
    const boost::shared_ptr<Texture> &texture) {

    m_textures[name] = texture;
}

boost::shared_ptr<Texture> Uniforms::getTexture(const std::string &name) const {
    auto it = m_textures.find(name);
    if(it != m_textures.end()) return it->second;

    Message3(Render, Error, "Couldn't get texture with name \"" << name
        << "\" from uniforms");
    return nullptr;
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

    for(auto &c : m_colours) {
        program->setUniform(c.first, c.second);
    }

    for(auto &m : m_matrices) {
        program->setUniform(m.first, m.second);
    }

    for(auto &t : m_textures) {
        program->setUniform(t.first, t.second);
    }
}

void Uniforms::add(const Uniforms &other) {
    for(auto &it : other.m_ints) m_ints[it.first] = it.second;
    for(auto &it : other.m_floats) m_floats[it.first] = it.second;
    for(auto &it : other.m_vectors) m_vectors[it.first] = it.second;
    for(auto &it : other.m_colours) m_colours[it.first] = it.second;
    for(auto &it : other.m_matrices) m_matrices[it.first] = it.second;
    for(auto &it : other.m_textures) m_textures[it.first] = it.second;
}

void Uniforms::add(const boost::shared_ptr<Uniforms> &other) {
    add(*other);
}

}  // namespace Render
}  // namespace Kriti
