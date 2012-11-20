#include "Shader.h"

#include "ResourceRegistry.h"
#include "FileResource.h"

namespace Kriti {
namespace Render {

Shader::Shader() {

}

Shader::~Shader() {

}

bool Shader::loadFrom(std::string identifier) {
    boost::shared_ptr<FileResource> shaderFile
        = ResourceRegistry::instance()->get<FileResource>(
            "shaders/" + identifier + ".glsl");
    return false;
}

}  // namespace Render
}  // namespace Kriti
