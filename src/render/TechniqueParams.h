#ifndef KRITI_RENDER__TECHNIQUE_PARAMS_H
#define KRITI_RENDER__TECHNIQUE_PARAMS_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Technique;
class Texture;

class TechniqueParams {
private:
    std::vector<std::pair<std::string, int>> m_ints;
    std::vector<std::pair<std::string, Math::Matrix>> m_matrices;
    std::vector<std::pair<std::string, boost::shared_ptr<Texture>>> m_textures;
public:
    void addParam(std::string uniform, int value);
    void addParam(std::string uniform, const Math::Matrix &matrix);
    void addParam(std::string uniform, boost::shared_ptr<Texture> texture);

    /// assumes technique is already activated
    void set(boost::shared_ptr<Technique> technique) const;
};

}  // namespace Render
}  // namespace Kriti

#endif
