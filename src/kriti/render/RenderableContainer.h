#ifndef KRITI_RENDER__RENDERABLE_CONTAINER_H
#define KRITI_RENDER__RENDERABLE_CONTAINER_H

#include <set>

#include <boost/function.hpp>

#include "Renderable.h"
#include "UniformHook.h"

namespace Kriti {
namespace Render {

class RenderableContainer {
public:
    typedef boost::function<void (boost::shared_ptr<Renderable>)> IteratorType;
private:
    std::set<boost::shared_ptr<Renderable>> m_renderables, m_transRenderables;
    std::set<boost::shared_ptr<RenderableContainer>> m_containers;

    std::vector<boost::shared_ptr<UniformHook>> m_uniformHooks;
public:
    void add(boost::shared_ptr<Renderable> renderable)
        { m_renderables.insert(renderable); }
    void addTransparent(boost::shared_ptr<Renderable> renderable)
        { m_transRenderables.insert(renderable); }
    void add(boost::shared_ptr<RenderableContainer> container)
        { m_containers.insert(container); }
    void remove(boost::shared_ptr<Renderable> renderable)
        { m_renderables.erase(m_renderables.find(renderable)); }
    void removeTransparent(boost::shared_ptr<Renderable> renderable)
        { m_transRenderables.erase(m_transRenderables.find(renderable)); }
    void remove(boost::shared_ptr<RenderableContainer> container)
        { m_containers.erase(m_containers.find(container)); }

    void addUniformHook(boost::shared_ptr<UniformHook> hook)
        { m_uniformHooks.push_back(hook); }

    void draw(Uniforms &globalParams, 
        std::map<boost::weak_ptr<Material>, Uniforms> &materialParams);

    void iterate(IteratorType iterator);
private:
    void iterate(IteratorType iterator,
        std::set<boost::shared_ptr<Renderable>> &visited);
    void draw(Uniforms &globalParams, 
        std::map<boost::weak_ptr<Material>, Uniforms> &materialParams,
        std::set<boost::shared_ptr<Renderable>> &visited);
};

}  // namespace Render
}  // namespace Kriti

#endif
