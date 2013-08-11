#ifndef KRITI_GUI__OUTLINE_REGISTRY_H
#define KRITI_GUI__OUTLINE_REGISTRY_H

#include <map>

#include <boost/weak_ptr.hpp>

#include "math/Vector.h"

namespace Kriti {
namespace GUI {

class LayoutItem;

class OutlineRegistry {
private:
    typedef std::pair<Math::Vector, Math::Vector> Rectangle;
    std::map<boost::weak_ptr<LayoutItem>, Rectangle> m_outlines;
public:
    void updateOutline(boost::weak_ptr<LayoutItem> item, Math::Vector pos,
        Math::Vector size);

    boost::weak_ptr<LayoutItem> topItemAt(Math::Vector pos);
};

}  // namespace GUI
}  // namespace Kriti

#endif
