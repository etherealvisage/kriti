#ifndef KRITI_GUI__LAYOUT_SPACER_H
#define KRITI_GUI__LAYOUT_SPACER_H

#include "LayoutItem.h"

namespace Kriti {
namespace GUI {

class LayoutSpacer : public LayoutItem {
private:
    Math::Vector m_minSize, m_stretch;
public:
    LayoutSpacer(Math::Vector minSize, Math::Vector stretch)
        : m_minSize(minSize), m_stretch(stretch) {}

    virtual Math::Vector minSize() { return m_minSize; }
    virtual Math::Vector stretch() { return m_stretch; }
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd) {}
};

}  // namespace GUI
}  // namespace Kriti

#endif
