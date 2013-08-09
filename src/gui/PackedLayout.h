#ifndef KRITI_GUI__PACKED_LAYOUT_H
#define KRITI_GUI__PACKED_LAYOUT_H

#include "Layout.h"

namespace Kriti {
namespace GUI {

class PackedLayout : public Layout {
public:
    enum PackDirection {
        Horizontal,
        Vertical
    };
private:
    PackDirection m_dir;
public:
    PackedLayout(Math::Vector stretch, PackDirection dir = Vertical)
        : Layout(stretch), m_dir(dir) {}

    virtual Math::Vector minSize();
protected:
    virtual void updated();
};

}  // namespace GUI
}  // namespace Kriti

#endif
