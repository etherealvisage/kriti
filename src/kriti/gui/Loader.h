#ifndef KRITI_GUI__LOADER_H
#define KRITI_GUI__LOADER_H

#include <string>
#include <map>

#include "Widget.h"
#include "Layout.h"

#include "../Globals.h"
#include "../XMLResource.h"

namespace Kriti {
namespace GUI {

class Loader { KRITI_GLOBAL(Loader)
private:
    std::map<std::string, boost::shared_ptr<Widget>> m_guis;
    std::map<std::string, boost::shared_ptr<Widget>> m_namedWidgets;
public:
    Loader() { load(); }
public:
    template<typename T>
    boost::shared_ptr<T> guiByName(std::string name) {
        return boost::dynamic_pointer_cast<T>(m_guis[name]);
    }
    template<typename T>
    boost::shared_ptr<T> widgetByName(std::string name) {
        return boost::dynamic_pointer_cast<T>(m_namedWidgets[name]);
    }
private:
    void load();
    boost::shared_ptr<Widget> loadWidget(const pugi::xml_node &from);
    boost::shared_ptr<Layout> loadLayout(const pugi::xml_node &from);
};

}  // namespace GUI
}  // namespace Kriti

#endif
