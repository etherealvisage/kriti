#include "Technique.h"
#include "config/Tree.h"
#include "ResourceRegistry.h"

namespace Kriti {
namespace Render {

Technique::Technique() {

}

bool Technique::loadFrom(std::string identifier) {
    if(identifier == "") return false;
    boost::shared_ptr<Config::Tree> tree = Config::Tree::instance();

    std::string tbase = "techniques." + identifier;

    m_vertexShaderName = tree->getString(tbase + ".vertexShader", "");
    m_vertexShader = ResourceRegistry::instance()->get<Shader>(
        m_vertexShaderName);
    if(!m_vertexShader) {
        Message3(Render, Error, "Could not find vertex shader \""
            << m_vertexShaderName << "\"");
        return false;
    }
    m_fragShaderName = tree->getString(tbase + ".vertexShader", "");
    m_fragShader = ResourceRegistry::instance()->get<Shader>(
        m_vertexShaderName);
    if(!m_fragShader) {
        Message3(Render, Error, "Could not find frag shader \""
            << m_vertexShaderName << "\"");
        return false;
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
