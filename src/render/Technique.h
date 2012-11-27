#ifndef KRITI_RENDER__TECHNIQUE_H
#define KRITI_RENDER__TECHNIQUE_H

#include <boost/shared_ptr.hpp>

#include <map>

#include "Resource.h"
#include "Shader.h"

#include "math/Matrix.h"

namespace Kriti {
namespace Render {

class Technique : public Resource {
private:
    std::string m_vertexShaderName;
    boost::shared_ptr<Shader> m_vertexShader;
    std::string m_fragShaderName;
    boost::shared_ptr<Shader> m_fragShader;

    GLuint m_programID;

    std::map<std::string, GLint> m_uniformLocations;
public:
    Technique();
    
    virtual bool loadFrom(std::string identifier);

    void setUniform(const std::string &name, const Math::Matrix &matrix);

    void activate();
private:
    GLint getUniformLocation(const std::string &name);
};

}  // namespace Render
}  // namespace Kriti

#endif
