#include <boost/make_shared.hpp>

#include "Loader.h"

#include "Panel.h"
#include "Label.h"
#include "Button.h"
#include "PackedLayout.h"

#include "MessageSystem.h"
#include "ResourceRegistry.h"
#include "XMLResource.h"

namespace Kriti {
namespace GUI {

boost::shared_ptr<Loader> Loader::s_singleton;

void Loader::load() {
    auto node = ResourceRegistry::get<XMLResource>(
            "data"
        )->doc().first_element_by_path(
            "/kriti/guis"
        );

    if(!node) {
        Message3(GUI, Debug, "No GUIs specified in data file!");
        return;
    }

    for(auto child : node) {
        std::string guiName = child.attribute("name").as_string("");
        m_guis[guiName] = loadWidget(child.child("widget"));
    }
}

boost::shared_ptr<Widget> Loader::loadWidget(const pugi::xml_node &from) {
    std::string type = from.attribute("type").as_string("");
    if(type == "") {
        Message3(GUI, Error, "Widget element missing type");
        return boost::shared_ptr<Widget>();
    }

    if(type == "panel") {
        auto lnode = from.child("layout");
        if(!lnode) {
            Message3(GUI, Error, "Panel element missing layout");
            return boost::shared_ptr<Widget>();
        }

        boost::shared_ptr<Layout> layout = loadLayout(lnode);
        if(!layout) {
            Message3(GUI, Error, "Panel layout loading failed");
            return boost::shared_ptr<Widget>();
        }

        for(auto wnode = from.child("widget"); wnode;
            wnode = wnode.next_sibling()) {
            
            //Message3(GUI, Debug, "Widget sibling");
            auto widget = loadWidget(wnode);
            if(widget) layout->addItem(widget);
        }
        //auto panel = boost::make_shared<Panel>();
    }
    else if(type == "label") {
        
    }

    return boost::shared_ptr<Widget>();
}

boost::shared_ptr<Layout> Loader::loadLayout(const pugi::xml_node &from) {
    boost::shared_ptr<Layout> layout;

    std::string ltype = from.attribute("type").as_string("");

    if(ltype == "") {
         Message3(GUI, Error, "Layout missing type");
         return boost::shared_ptr<Layout>();
    }
    else if(ltype == "packed") {
        std::string dirs = from.attribute(
            "direction").as_string("vertical");

        PackedLayout::PackDirection direction;
        if(dirs== "vertical") direction = PackedLayout::Vertical;
        else if(dirs == "horizontal") direction = PackedLayout::Horizontal;
        else {
            Message3(GUI, Error, "Packed layout invalid direction");
            return boost::shared_ptr<Layout>();
        }
        layout = boost::make_shared<PackedLayout>(Math::Vector(1.0, 1.0),
            direction);
    }
    else {
        Message3(GUI, Error, "Layout invalid type");
        return boost::shared_ptr<Layout>();
    }
    return layout;
}

}  // namespace GUI
}  // namespace Kriti
