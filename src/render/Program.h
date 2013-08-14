#ifndef KRITI_RENDER__PROGRAM_H
#define KRITI_RENDER__PROGRAM_H

#include <boost/shared_ptr.hpp>

#include <map>

#include "Shader.h"

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Texture;
class TextureContext;

class Program {
private:
    boost::shared_ptr<TextureContext> m_textureContext;

    std::string m_vsName;
    boost::shared_ptr<Shader> m_vertexShader;
    std::string m_fsName;
    boost::shared_ptr<Shader> m_fragShader;

    GLuint m_programID;

    std::map<std::string, GLint> m_uniformLocations;
public:
    Program(std::string vsName, std::string fsName);
    
    void setUniform(const std::string &name, const Math::Matrix &matrix);
    void setUniform(const std::string &name, int value);
    void setUniform(const std::string &name, float value);
    void setUniform(const std::string &name,
        boost::shared_ptr<Texture> texture);

    void activate(boost::shared_ptr<TextureContext> textureContext);
private:
    GLint getUniformLocation(const std::string &name);
};

}  // namespace Render
}  // namespace Kriti

#endif
