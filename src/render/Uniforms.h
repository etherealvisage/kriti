#ifndef KRITI_RENDER__UNIFORMS_H
#define KRITI_RENDER__UNIFORMS_H

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Texture;
class Program;

class Uniforms {
private:
    std::map<std::string, int> m_ints;
    std::map<std::string, float> m_floats;
    std::map<std::string, Math::Matrix> m_matrices;
    std::map<std::string, boost::shared_ptr<Texture>> m_textures;
public:
    void setParam(std::string name, int value);
    void setParam(std::string name, float value);
    void setParam(std::string name, double value)
        { setParam(name, (float)value); }
    void setParam(std::string name, const Math::Matrix &matrix);
    void setParam(std::string name, boost::shared_ptr<Texture> texture);

    /// assumes program is already activated
    void set(boost::shared_ptr<Program> program) const;
};

}  // namespace Render
}  // namespace Kriti

#endif
