#ifndef KRITI_GUI__LAYOUT_ITEM_H
#define KRITI_GUI__LAYOUT_ITEM_H

#include <boost/enable_shared_from_this.hpp>

#include "OutlineRegistry.h"
#include "MouseState.h"
#include "Style.fwd"
#include "Context.fwd"

#include "../math/Vector.h"
#include "../math/AffineTransformation.h"

#include "../render/RenderableContainer.h"

#include "../state/Context.fwd"

namespace Kriti {
namespace GUI {

class LayoutItem : public boost::enable_shared_from_this<LayoutItem> {
    friend class Context;
private:
    /// stores the calculated size of the layout item.
    Math::Vector m_pos, m_size, m_scale;
    MouseState m_mouseState;
    boost::shared_ptr<Style> m_style;
    boost::shared_ptr<State::Context> m_context;
    LayoutItem *m_parent;
    boost::weak_ptr<Context> m_guiContext;
    bool m_wasSet;
    bool m_wasClicked;
public:
    LayoutItem();
    virtual ~LayoutItem() {}

    virtual Math::Vector minSize() = 0;
    virtual Math::Vector stretch() = 0;

    /// stubbed by default, called on an update for various hooks.
    void update(boost::shared_ptr<OutlineRegistry> registry, Math::Vector pos,
        Math::Vector size, Math::Vector scale)
        { update(registry, pos, size, scale, pos, pos+size); }
    void update(boost::shared_ptr<OutlineRegistry> registry, Math::Vector pos,
        Math::Vector size, Math::Vector scale, Math::Vector clipStart,
        Math::Vector clipEnd);

    /// fill in/register all renderables into the container
    /// should be re-implemented in derived types
    virtual void fill(boost::shared_ptr<Render::RenderableContainer>
        __attribute__((unused)) container) {}
    /// flush all related renderables out of the given container
    /// should be re-implemented in derived types
    virtual void flush(boost::shared_ptr<Render::RenderableContainer>
        __attribute__((unused)) container) {}

    Math::Vector pos() const { return m_pos; }
    Math::Vector size() const { return m_size; }
    Math::Vector scale() const { return m_scale; }

    MouseState mouseState() const { return m_mouseState; }
    void updateMouseState(MouseState newms) { m_mouseState = newms; }

    boost::shared_ptr<Style> style() const { return m_style; }
    void changeStyle(boost::shared_ptr<Style> style) { m_style = style; }

    boost::shared_ptr<State::Context> eventContext() const
        { return m_context; }

    LayoutItem *parent() const { return m_parent; }
    boost::weak_ptr<Context> guiContext() const { return m_guiContext; }
    boost::weak_ptr<Context> findGuiContext() const;
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd) = 0;
    void standardOutlineUpdate(boost::shared_ptr<OutlineRegistry> registry,
        const Math::Vector &clipStart, const Math::Vector &clipEnd,
        Math::Vector &outlineStart, Math::Vector &outlineEnd);

    void createEventContext();
    void setParent(LayoutItem *parent) { m_parent = parent; }
    void reparent(boost::shared_ptr<LayoutItem> item)
        { if(item) item->m_parent = this; }
    void unparent(boost::shared_ptr<LayoutItem> item)
        { if(item) item->m_parent = nullptr; }
    void setContext(boost::weak_ptr<Context> context)
        { m_guiContext = context; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
