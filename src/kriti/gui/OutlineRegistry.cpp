#include "OutlineRegistry.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

void OutlineRegistry::updateOutline(boost::weak_ptr<LayoutItem> widget,
    Math::Vector pos, Math::Vector size) {
    
    m_outlines[widget] = std::make_pair(pos, size);
}

boost::weak_ptr<LayoutItem> OutlineRegistry::topItemAt(Math::Vector pos) {
    std::vector<boost::weak_ptr<LayoutItem>> toRemove;

    boost::weak_ptr<LayoutItem> best;
    double bestZ = -1e100;
    for(auto outline : m_outlines) {
        auto widget = outline.first.lock();
        if(!widget) { toRemove.push_back(outline.first); continue; }

        if(outline.second.first.x() > pos.x()) continue;
        if(outline.second.first.y() > pos.y()) continue;

        if(outline.second.first.x()+outline.second.second.x() < pos.x())
            continue;
        if(outline.second.first.y()+outline.second.second.y() < pos.y())
            continue;

        if(bestZ > outline.second.first.z()) continue;

        best = outline.first;
        bestZ = outline.second.first.z();
    }

    return best;
}

}  // namespace GUI
}  // namespace Kriti
