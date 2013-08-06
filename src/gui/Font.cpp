#include <GL/glew.h>

#include "Font.h"

#include "render/Texture.h"

#include "config/Tree.h"

#include "MessageSystem.h"
#include "ResourceRegistry.h"
#include "FileResource.h"

namespace Kriti {
namespace GUI {

bool Font::loadFrom(std::string identifier) {
    Message3(GUI, Debug, "Loading font \"" << identifier << "\"");
    auto ctree = Config::Tree::instance();
    std::string texture_name
        = ctree->getString("fonts." + identifier + ".texture_name");

    auto texture
        = ResourceRegistry::instance()->get<Render::Texture>(texture_name);
    if(!texture) return false;

    std::string desc_name
        = ctree->getString("fonts." + identifier + ".description_name");

    auto desc
        = ResourceRegistry::instance()->get<FileResource>(desc_name);
    if(!desc) return false;

    return true;
}

}  // namespace GUI
}  // namespace Kriti
