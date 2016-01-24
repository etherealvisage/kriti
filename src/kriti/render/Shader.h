#ifndef KRITI_RENDER__SHADER_H
#define KRITI_RENDER__SHADER_H

#include "../ogl.h"

#include "../Resource.h"

namespace Kriti {
namespace Render {

class Shader : public Resource {
private:
    GLuint m_shaderID;
public:
    Shader();
    ~Shader();

    GLuint shaderID() const { return m_shaderID; }

    virtual bool loadFrom(std::string identifier);
};

}  // namespace Render
}  // namespace Kriti

#endif
