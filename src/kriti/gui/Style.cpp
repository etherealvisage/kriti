#include <cstring>

#include <boost/make_shared.hpp>

#include "Style.h"

#include "../render/Uniforms.h"

#include "../XMLResource.h"
#include "../ResourceRegistry.h"

namespace Kriti {
namespace GUI {

Style::Style() {
    m_uniforms = boost::make_shared<Render::Uniforms>();

    m_uniforms->setParam("gui_style_panel_border_width", 0.1);
    m_uniforms->setParam("gui_style_panel_dropoff", 0.3);
    m_uniforms->setParam("gui_style_panel_background",
        Math::Colour(0.0, 0.0, 0.0, 0.5));
    m_uniforms->setParam("gui_style_panel_activated",
        Math::Colour(0.0, 0.3, 0.3, 0.5));
    m_uniforms->setParam("gui_style_panel_neutral",
        Math::Colour(0.3, 0.3, 0.0, 1.0));

    m_uniforms->setParam("gui_style_button_border_width", 0.1);
    m_uniforms->setParam("gui_style_button_panel_activated",
        Math::Colour(0.1, 0.1, 0.0, 1.0));
    m_uniforms->setParam("gui_style_button_panel_deactivated",
        Math::Colour(0.4, 0.4, 0.0, 1.0));
    m_uniforms->setParam("gui_style_button_panel_clicked",
        Math::Colour(0.4, 0.4, 0.4, 1.0));
    m_uniforms->setParam("gui_style_button_border_activated",
        Math::Colour(1.0, 1.0, 0.0, 1.0));
    m_uniforms->setParam("gui_style_button_border_deactivated",
        Math::Colour(0.1, 0.1, 0.0, 1.0));
}

bool Style::loadFrom(std::string identifier) {
    auto xml = ResourceRegistry::get<XMLResource>(
        "gui/" + identifier + "_style");
    if(!xml) return false;

    Message3(GUI, Debug, "Loading GUI style \"" << identifier << "\"!");

    const auto &style = xml->doc().first_element_by_path("/style");

    for(pugi::xml_node n = style.first_child(); n; n = n.next_sibling()) {
        Message3(GUI, Debug, "processing next node");
        if(!std::strcmp(n.name(), "float")) {
            m_uniforms->setParam(
                std::string("gui_style_") + n.attribute("name").as_string(),
                n.text().as_double());
        }
        else if(!std::strcmp(n.name(), "colour")
            || !std::strcmp(n.name(), "color")) {

            m_uniforms->setParam(
                std::string("gui_style_") + n.attribute("name").as_string(),
                Math::Colour(n.text().as_string()));
        }
    }

    return true;
}

}  // namespace GUI
}  // namespace Kriti
