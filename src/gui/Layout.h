#ifndef KRITI_GUI__LAYOUT_H
#define KRITI_GUI__LAYOUT_H

#include <vector>

#include <boost/shared_ptr.hpp>

#include "LayoutItem.h"

namespace Kriti {
namespace GUI {

class Layout : public LayoutItem {
private:
    Math::Vector m_stretch;
    std::vector<boost::shared_ptr<LayoutItem>> m_items;
public:
    Layout(Math::Vector stretch) : m_stretch(stretch) {}
    virtual ~Layout() {}

    virtual Math::Vector stretch() const { return m_stretch; }

    void addItem(boost::shared_ptr<LayoutItem> item)
        { m_items.push_back(item); }
};

}  // namespace GUI
}  // namespace Kriti

#endif
