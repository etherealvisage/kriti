#include "TechniqueParams.h"
#include "Technique.h"

namespace Kriti {
namespace Render {

void TechniqueParams::addParam(std::string uniform, int value) {
    m_ints.push_back(std::make_pair(uniform, value));
}

void TechniqueParams::addParam(std::string uniform,
    const Math::Matrix &matrix) {

    m_matrices.push_back(std::make_pair(uniform, matrix));
}

void TechniqueParams::addParam(std::string uniform,
    boost::shared_ptr<Texture> texture) {

    m_textures.push_back(std::make_pair(uniform, texture));
}

void TechniqueParams::set(boost::shared_ptr<Technique> technique) const {
    for(auto i : m_ints) {
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
