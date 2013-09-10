#ifndef KRITI_RENDER__RENDERABLE_CONTAINER_H
#define KRITI_RENDER__RENDERABLE_CONTAINER_H

#include <set>

#include <boost/function.hpp>

#include "Renderable.h"

namespace Kriti {
namespace Render {

class RenderableContainer {
public:
    typedef boost::function<void (boost::shared_ptr<Renderable>)> IteratorType;
private:
    std::set<boost::shared_ptr<Renderable>> m_renderables;
    std::set<boost::shared_ptr<RenderableContainer>> m_containers;
public:
    void add(boost::shared_ptr<Renderable> renderable)
        { m_renderables.insert(renderable); }
    void add(boost::shared_ptr<RenderableContainer> container)
        { m_containers.insert(container); }
    void remove(boost::shared_ptr<Renderable> renderable)
        { m_renderables.erase(m_renderables.find(renderable)); }
    void remove(boost::shared_ptr<RenderableContainer> container)
        { m_containers.erase(m_containers.find(container)); }

    void iterate(IteratorType iterator);
private:
    void iterate(IteratorType iterator,
        std::set<boost::shared_ptr<Renderable>> &visited);
};

}  // namespace Render
}  // namespace Kriti

#endif
