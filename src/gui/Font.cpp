#include <sstream>

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
    m_materialName 
        = ctree->getString("fonts." + identifier + ".material_name");

    if(m_materialName == "") return false;

    std::string desc_name
        = ctree->getString("fonts." + identifier + ".description_name");

    auto desc = ResourceRegistry::instance()->get<FileResource>(  
        "fonts/" + desc_name);
    if(!desc) return false;

    std::istringstream iss(desc->fileContent());

    int texture_width
        = ctree->getInt("fonts." + identifier + ".texture_width");
    int texture_height
        = ctree->getInt("fonts." + identifier + ".texture_height");

    int id;
    CharSpec cs;
    while(iss >> id >> cs.x >> cs.y >> cs.w >> cs.h >> cs.xoff >> cs.yoff
        >> cs.xadv) {

        cs.x /= texture_width;
        cs.w /= texture_width;
        cs.xoff /= texture_width;
        cs.xadv /= texture_width;
        cs.y /= texture_height;
        cs.h /= texture_height;
        cs.yoff /= texture_height;
        m_chars[id] = cs;
    }

    return true;
}

bool Font::getCharSpec(int c, CharSpec &cs) const {
    auto f = m_chars.find(c);
    if(f == m_chars.end()) return false;
    cs = f->second;
    return true;
}

}  // namespace GUI
}  // namespace Kriti
