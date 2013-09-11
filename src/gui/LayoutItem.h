#ifndef KRITI_GUI__LAYOUT_ITEM_H
#define KRITI_GUI__LAYOUT_ITEM_H

#include <boost/enable_shared_from_this.hpp>

#include "math/Vector.h"
#include "math/AffineTransformation.h"

#include "render/RenderableContainer.h"

#include "OutlineRegistry.h"
#include "MouseState.h"

namespace Kriti {
namespace GUI {

class LayoutItem : public boost::enable_shared_from_this<LayoutItem> {
private:
    /// stores the calculated size of the layout item.
    Math::Vector m_pos, m_size, m_scale;
    MouseState m_mouseState;
public:
    virtual ~LayoutItem() {}

    virtual Math::Vector minSize() = 0;
    virtual Math::Vector stretch() = 0;

    /// stubbed by default, called on an update for various hooks.
    void update(boost::shared_ptr<OutlineRegistry> registry, Math::Vector pos,
        Math::Vector size, Math::Vector scale)
        { m_pos = pos, m_size = size, m_scale = scale; updated(registry); }

    /// fill in/register all renderables into the container
    /// should be re-implemented in derived types
    virtual void fill(boost::shared_ptr<Render::RenderableContainer>
            __attribute__((unused)) container) {}
    
    Math::Vector pos() const { return m_pos; }
    Math::Vector size() const { return m_size; }
    Math::Vector scale() const { return m_scale; }

    MouseState mouseState() const { return m_mouseState; }
    void updateMouseState(MouseState newms) { m_mouseState = newms; }
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry) = 0;
};

}  // namespace GUI
}  // namespace Kriti

#endif
