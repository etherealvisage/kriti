#include "PackedLayout.h"

#include "Scale.h"

#include "MessageSystem.h"

namespace Kriti {
namespace GUI {

Math::Vector PackedLayout::minSize() {
    if(m_dir == Vertical) {
        double minY = 0.0;
        double maxX = 0.0;

        for(auto item : m_items) {
            maxX = std::max(item->minSize().x(), maxX);
            minY += item->minSize().y();
        }

        return Math::Vector(maxX, minY);
    }
    else return Math::Vector();
}

void PackedLayout::updated(boost::shared_ptr<OutlineRegistry> registry) {
    if(m_dir == Vertical) {
        double minY = 0.0;
        double stretchY = 0.0;

        for(auto item : m_items) {
            minY += item->minSize().y();
            stretchY += item->stretch().y();
        }

        if(stretchY == 0.0) stretchY = 1.0;

        double extraY = std::max(0.0, size().y() - minY);

        double cursor = 0.0;
        for(auto item : m_items) {
            double sfactor = item->stretch().y();
            double height = item->minSize().y();

            height += (sfactor / stretchY) * extraY;
            item->update(registry, pos() + Math::Vector(0.0, cursor),
                Math::Vector(size().x(), height), scale());

            cursor += height;
        }
    }
}

}  // namespace GUI
}  // namespace Kriti
