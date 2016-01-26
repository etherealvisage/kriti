#include "RenderableContainer.h"

namespace Kriti {
namespace Render {

void RenderableContainer::iterate(IteratorType iterator) {
    std::set<boost::shared_ptr<Renderable>> visited;
    iterate(iterator, visited);
}

void RenderableContainer::draw(Uniforms &globalParams, 
    std::map<boost::weak_ptr<Material>, Uniforms> &materialParams) {

    for(auto &hook : m_uniformHooks) {
        hook->hook(globalParams);
    }

    for(auto &renderable : m_renderables) {
        renderable->draw(globalParams, materialParams);
    }

    // TODO: depth-sort these?
    for(auto &renderable : m_transRenderables) {
        renderable->draw(globalParams, materialParams);
    }

    for(auto &container : m_containers) {
        // TODO: set up something to remove this copy
        Uniforms copy = globalParams;
        container->draw(copy, materialParams);
    }
}

void RenderableContainer::iterate(IteratorType iterator,
    std::set<boost::shared_ptr<Renderable> > &visited) {

    for(auto &renderable : m_renderables) {
        if(visited.find(renderable) != visited.end()) continue;
        visited.insert(renderable);

        iterator(renderable);
    }

    for(auto &container : m_containers) {
        container->iterate(iterator, visited);
    }

    // TODO: depth-sort these?
    for(auto &renderable : m_transRenderables) {
        if(visited.find(renderable) != visited.end()) continue;
        visited.insert(renderable);

        iterator(renderable);
    }
}

}  // namespace Render
}  // namespace Kriti
