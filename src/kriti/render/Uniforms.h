#ifndef KRITI_RENDER__UNIFORMS_H
#define KRITI_RENDER__UNIFORMS_H

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

#include "../math/Matrix.h"
#include "../math/Colour.h"

namespace Kriti {
namespace Render {

class Texture;
class Program;

class Uniforms {
private:
    std::map<std::string, int> m_ints;
    std::map<std::string, float> m_floats;
    std::map<std::string, Math::Vector> m_vectors;
    std::map<std::string, Math::Colour> m_colours;
    std::map<std::string, Math::Matrix> m_matrices;
    std::map<std::string, boost::shared_ptr<Texture>> m_textures;
public:
    void setParam(const std::string &name, int value);
    int getInt(const std::string &name) const;

    void setParam(const std::string &name, float value);
    float getFloat(const std::string &name) const;

    void setParam(const std::string &name, double value)
        { setParam(name, (float)value); }

    void setParam(const std::string &name, const Math::Vector &vector);
    Math::Vector getVector(const std::string &name) const;

    void setParam(const std::string &name, const Math::Colour &colour);
    Math::Colour getColour(const std::string &name) const;

    void setParam(const std::string &name, const Math::Matrix &matrix);
    Math::Matrix getMatrix(const std::string &name) const;

    void setParam(const std::string &name,
        const boost::shared_ptr<Texture> &texture);
    boost::shared_ptr<Texture> getTexture(const std::string &name) const;

    /// assumes program is already activated
    void set(boost::shared_ptr<Program> program) const;

    void add(const Uniforms &other);
    void add(const boost::shared_ptr<Uniforms> &other);
};

}  // namespace Render
}  // namespace Kriti

#endif
