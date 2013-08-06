#ifndef KRITI_GUI__LAYOUT_ITEM_H
#define KRITI_GUI__LAYOUT_ITEM_H

#include "math/Vector.h"

namespace Kriti {
namespace GUI {

class LayoutItem {
private:
    /// stores the calculated size of the layout item.
    Math::Vector m_size;
public:
    virtual ~LayoutItem() {}

    virtual Math::Vector minSize() = 0;
    virtual Math::Vector stretch() = 0;

    Math::Vector size() const { return m_size; }
    void setSize(Math::Vector size) { m_size = size; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
