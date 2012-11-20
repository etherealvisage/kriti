#ifndef KRITI_RENDER__SHADER_H
#define KRITI_RENDER__SHADER_H

#include "Resource.h"

namespace Kriti {
namespace Render {

class Shader : public Resource {
public:
    Shader();
    ~Shader();

    virtual bool loadFrom(std::string identifier);
};

}  // namespace Render
}  // namespace Kriti

#endif
