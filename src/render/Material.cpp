#include "Material.h"
#include "Texture.h"

#include "config/Tree.h"

#include "ResourceRegistry.h"

namespace Kriti {
namespace Render {

bool Material::loadFrom(std::string identifier) {
    Message3(Render, Debug, "Loading material " << identifier);
    auto ctree = Config::Tree::instance();

    m_techniqueName
        = ctree->getString("materials." + identifier + ".technique");
    if(m_techniqueName == "") {
        Message3(Render, Debug, "Technique name is empty.");
        return false;
    }

    m_technique
        = ResourceRegistry::instance()->get<Technique>(m_techniqueName);

    auto cnode = ctree->node("materials." + identifier + ".params");
    // if there's no uniforms, we're done.
    if(!cnode.lock()) {
        return true;
    }

    auto list = cnode.lock()->childList();

    for(auto name : list) {
        auto unode = cnode.lock()->child(name).lock();
        switch(unode->type()) {
        case Config::TreeNode::Integer: {
            m_params.setParam(name, unode->asInt());
            break;
        }
        case Config::TreeNode::Double: {
            m_params.setParam(name, unode->asDouble());
            break;
        }
        case Config::TreeNode::Vector: {
            //m_params.addParam(name, unode->asInt());
            Message3(Render, Fatal, "vector uniforms in material spec NYI.");
            break;
        }
        case Config::TreeNode::String: {
            Message3(Render, Debug, "string");
            m_params.setParam(name,
                ResourceRegistry::instance()->get<Texture>(unode->asString()));
            break;
        }
        default:
            Message3(Render, Error, "Only know how to handle uniforms of "
                "integer/double/vector/texture type.");
            break;
        }
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
