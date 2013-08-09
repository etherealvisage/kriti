#ifndef KRITI_GUI__LAYOUT_ITEM_H
#define KRITI_GUI__LAYOUT_ITEM_H

#include "math/Vector.h"
#include "math/AffineTransformation.h"

namespace Kriti {
namespace GUI {

class LayoutItem {
private:
    /// stores the calculated size of the layout item.
    Math::Vector m_pos, m_size, m_scale;
public:
    virtual ~LayoutItem() {}

    virtual Math::Vector minSize() = 0;
    virtual Math::Vector stretch() = 0;

    /// stubbed by default, called on an update for various hooks.
    void update(Math::Vector pos, Math::Vector size, Math::Vector scale)
        { m_pos = pos, m_size = size, m_scale = scale; updated(); }
    
    Math::Vector pos() const { return m_pos; }
    Math::Vector size() const { return m_size; }
    Math::Vector scale() const { return m_scale; }
protected:
    virtual void updated() = 0;
};

}  // namespace GUI
}  // namespace Kriti

#endif
