#ifndef KRITI_GUI__CONTEXT_H
#define KRITI_GUI__CONTEXT_H

#include <vector>

#include <boost/tuple/tuple.hpp>

#include "kriti/state/Context.fwd"

#include "MouseCursor.h"
#include "MouseInteractor.h"
#include "OutlineRegistry.h"

#include "../render/RenderableContainer.fwd"

namespace Kriti {
namespace GUI {

class Context {
private:
    boost::shared_ptr<OutlineRegistry> m_outlineRegistry;
    boost::shared_ptr<MouseInteractor> m_mouseInteractor;
    boost::shared_ptr<MouseCursor> m_mouseCursor;

    std::vector<boost::tuple<boost::shared_ptr<LayoutItem>, Math::Vector,
        Math::Vector, Math::Vector>> m_rootItems;

    bool m_enabled;
    boost::shared_ptr<Render::RenderableContainer> m_container;
public:
    Context();

    bool enabled() const { return m_enabled; }
    void setEnabled(bool enabled) { m_enabled = enabled; }

    void hookOnto(boost::shared_ptr<State::Context> context);

    boost::shared_ptr<Render::RenderableContainer> container() const
        { return m_container; }

    void addRootItem(boost::shared_ptr<LayoutItem> item, Math::Vector location,
        Math::Vector size, Math::Vector scale);
private:
    void update();
};

}  // namespace GUI
}  // namespace Kriti

#endif
