#ifndef KRITI_RENDER__TECHNIQUE_PARAMS_H
#define KRITI_RENDER__TECHNIQUE_PARAMS_H

#include <string>
#include <vector>
#include <map>

#include <boost/shared_ptr.hpp>

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Technique;
class Texture;

class TechniqueParams {
private:
    std::map<std::string, int> m_intLocs, m_floatLocs, m_matrixLocs, m_texLocs;
    std::vector<std::pair<std::string, int>> m_ints;
    std::vector<std::pair<std::string, float>> m_floats;
    std::vector<std::pair<std::string, Math::Matrix>> m_matrices;
    std::vector<std::pair<std::string, boost::shared_ptr<Texture>>> m_textures;
public:
    void setParam(std::string uniform, int value);
    void setParam(std::string uniform, float value);
    void setParam(std::string uniform, double value)
        { setParam(uniform, (float)value); }
    void setParam(std::string uniform, const Math::Matrix &matrix);
    void setParam(std::string uniform, boost::shared_ptr<Texture> texture);

    /// assumes technique is already activated
    void set(boost::shared_ptr<Technique> technique) const;
};

}  // namespace Render
}  // namespace Kriti

#endif
