#include "TechniqueParams.h"
#include "Technique.h"

namespace Kriti {
namespace Render {

void TechniqueParams::setParam(std::string uniform, int value) {
    if(m_intLocs.find(uniform) == m_intLocs.end()) {
        m_ints.push_back(std::make_pair(uniform, value));
        m_intLocs[uniform] = m_ints.size()-1;
    }
    else m_ints[m_intLocs[uniform]] = std::make_pair(uniform, value);
}

void TechniqueParams::setParam(std::string uniform, float value) {
    if(m_floatLocs.find(uniform) == m_floatLocs.end()) {
        m_floats.push_back(std::make_pair(uniform, value));
        m_floatLocs[uniform] = m_floats.size()-1;
    }
    else m_floats[m_floatLocs[uniform]] = std::make_pair(uniform, value);
}

void TechniqueParams::setParam(std::string uniform,
    const Math::Matrix &matrix) {

    if(m_matrixLocs.find(uniform) == m_matrixLocs.end()) {
        m_matrices.push_back(std::make_pair(uniform, matrix));
        m_matrixLocs[uniform] = m_matrices.size()-1;
    }
    else m_matrices[m_matrixLocs[uniform]] = std::make_pair(uniform, matrix);
}

void TechniqueParams::setParam(std::string uniform,
    boost::shared_ptr<Texture> texture) {

    if(m_texLocs.find(uniform) == m_texLocs.end()) {
        m_textures.push_back(std::make_pair(uniform, texture));
        m_texLocs[uniform] = m_textures.size()-1;
    }
    else m_textures[m_texLocs[uniform]] = std::make_pair(uniform, texture);
}

void TechniqueParams::set(boost::shared_ptr<Technique> technique) const {
    for(auto i : m_ints) {
        technique->setUniform(i.first, i.second);
    }

    for(auto i : m_floats) {
        technique->setUniform(i.first, i.second);
    }

    for(auto m : m_matrices) {
        technique->setUniform(m.first, m.second);
    }

    for(auto t : m_textures) {
        technique->setUniform(t.first, t.second);
    }
}

}  // namespace Render
}  // namespace Kriti
