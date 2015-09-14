#include <sstream>

#include <GL/glew.h>

#include "Font.h"

#include "../render/Texture.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"
#include "../FileResource.h"
#include "../XMLResource.h"

namespace Kriti {
namespace GUI {

bool Font::loadFrom(std::string identifier) {
    Message3(GUI, Debug, "Loading font \"" << identifier << "\"");
    const pugi::xml_node &fontNode =
        ResourceRegistry::get<XMLResource>(
        "data")->doc().first_element_by_path(
        "/kriti/fonts").find_child_by_attribute(
        "font", "name", identifier.c_str());

    m_materialName = fontNode.child("material").text().as_string("");

    if(m_materialName == "") return false;

    std::string desc_name = fontNode.child("description").text().as_string("");

    auto desc = ResourceRegistry::get<FileResource>(  
        "fonts/" + desc_name + ".txt");
    if(!desc) return false;

    std::istringstream iss(desc->fileContent());

    int texture_width
        = fontNode.child("texture").attribute("width").as_int(0);
    int texture_height
        = fontNode.child("texture").attribute("height").as_int(0);

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
