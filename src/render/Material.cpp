#include <cstring>

#include <boost/make_shared.hpp>

#include "Material.h"
#include "Texture.h"

#include "ResourceRegistry.h"
#include "XMLResource.h"

namespace Kriti {
namespace Render {

bool Material::loadFrom(std::string identifier) {
    Message3(Render, Debug, "Loading material " << identifier);

    auto node = ResourceRegistry::get<XMLResource>(
        "data")->doc().first_element_by_path(
        "/kriti/materials/").find_child_by_attribute("name",
        identifier.c_str());

    std::string vsName = node.child("vertex-shader").text().as_string("");
    std::string fsName = node.child("fragment-shader").text().as_string("");
    std::string gsName = node.child("geometry-shader").text().as_string("");

    if(vsName == "") {
        Message3(Render, Error, "Vertex shader not specified for material "
            << identifier);
        return false;
    }
    if(fsName == "") {
        Message3(Render, Error, "Fragment shader not specified for material "
            << identifier);
        return false;
    }

    // missing geometry shader is not an error.

    m_program = boost::make_shared<Program>(vsName, fsName, gsName);

    for(auto child : node.children()) {
        if(std::strcmp(child.name(), "uniform")) continue;

        std::string name = child.attribute("name").as_string("");
        if(name == "") {
            Message3(Render, Error, "Missing name for uniform in material "
                << identifier);
            continue;
        }

        std::string type = child.attribute("type").as_string("");
        if(type == "") {
            Message3(Render, Error, "Missing type for uniform " << name
                << " in material " << identifier);
            continue;
        }

        if(type == "int") {
            m_params.setParam(name, child.text().as_int(0));
        }
        else if(type == "float") {
            m_params.setParam(name, child.text().as_float(0));
        }
        else if(type == "string") {
            m_params.setParam(name,
                ResourceRegistry::get<Texture>(child.text().as_string("")));
        }
        else {
            Message3(Render, Error, "Unknown type for uniform " << name
                <<" in material " << identifier);
        }
    }

    return true;
}

}  // namespace Render
}  // namespace Kriti
