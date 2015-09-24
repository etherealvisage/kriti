#ifndef KRITI_GUI__ITEM_SCALER_H
#define KRITI_GUI__ITEM_SCALER_H

#include "LayoutItem.h"

namespace Kriti {
namespace GUI {

class ItemScaler : public LayoutItem {
private:
    boost::shared_ptr<LayoutItem> m_child;
    double m_factor;
public:
    ItemScaler() : m_factor(1.0) {}

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);

    void setChild(boost::shared_ptr<LayoutItem> child) { m_child = child; }

    double factor() const { return m_factor; }
    void setFactor(double factor) { m_factor = factor; }

    virtual Math::Vector minSize();
    virtual Math::Vector stretch();
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);
};

}  // namespace GUI
}  // namespace Kriti

#endif
