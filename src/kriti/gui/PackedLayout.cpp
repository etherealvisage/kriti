#include <boost/range/adaptor/reversed.hpp>

#include "PackedLayout.h"

#include "Scale.h"

#include "../MessageSystem.h"

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

        if(m_items.size() > 0) {
            minY += (m_items.size()-1) * Scale().padding().y() * scale().y();
        }

        return Math::Vector(maxX, minY);
    }
    else return Math::Vector();
}

void PackedLayout::updated(boost::shared_ptr<OutlineRegistry> registry,
    Math::Vector clipStart, Math::Vector clipEnd) {

    if(m_dir == Vertical) {
        double minY = 0.0;
        double stretchY = 0.0;
        double ypad = Scale().padding().y() * scale().y();

        for(auto item : m_items) {
            minY += item->minSize().y();
            stretchY += item->stretch().y();
        }

        if(m_items.size() > 1) {
            minY += (m_items.size()-1) * ypad;
        }

        if(stretchY == 0.0) stretchY = 1.0;

        double extraY = size().y() - minY;
        if(extraY < 0) {
            Message3(GUI, Debug,
                "Trying to pack GUI items into too small of a space!");
            extraY = 0.0;
        }

        double cursor = 0.0;
        for(auto item : boost::adaptors::reverse(m_items)) {
            double sfactor = item->stretch().y();
            double height = item->minSize().y();

            height += (sfactor / stretchY) * extraY;
            item->update(registry, pos() + Math::Vector(0.0, cursor),
                Math::Vector(size().x(), height), scale(), clipStart, clipEnd);

            cursor += height;
            cursor += ypad;
        }
    }
}

}  // namespace GUI
}  // namespace Kriti
