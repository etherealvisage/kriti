#ifndef KRITI_RENDER__TECHNIQUE_H
#define KRITI_RENDER__TECHNIQUE_H

#include <boost/shared_ptr.hpp>

#include "Resource.h"

#include "Shader.h"

namespace Kriti {
namespace Render {

class Technique : public Resource {
private:
    std::string m_vertexShaderName;
    boost::shared_ptr<Shader> m_vertexShader;
    std::string m_fragShaderName;
    boost::shared_ptr<Shader> m_fragShader;
public:
    Technique();
    
    virtual bool loadFrom(std::string identifier);
};

}  // namespace Render
}  // namespace Kriti

#endif
