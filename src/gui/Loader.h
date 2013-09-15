#ifndef KRITI_GUI__LOADER_H
#define KRITI_GUI__LOADER_H

#include <string>
#include <map>

#include "Widget.h"
#include "Layout.h"

#include "XMLResource.h"

namespace Kriti {
namespace GUI {

class Loader {
private:
    static boost::shared_ptr<Loader> s_singleton;
public:
    static boost::shared_ptr<Loader> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<Loader>(new Loader());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    std::map<std::string, boost::shared_ptr<Widget>> m_guis;
    std::map<std::string, boost::shared_ptr<Widget>> m_namedWidgets;
private:
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
