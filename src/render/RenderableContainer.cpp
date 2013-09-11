#include "RenderableContainer.h"

namespace Kriti {
namespace Render {

void RenderableContainer::iterate(IteratorType iterator) {
    std::set<boost::shared_ptr<Renderable>> visited;
    iterate(iterator, visited);
}

void RenderableContainer::iterate(IteratorType iterator,
    std::set<boost::shared_ptr<Renderable> > &visited) {

    for(auto renderable : m_renderables) {
        if(visited.find(renderable) != visited.end()) continue;
        visited.insert(renderable);

        iterator(renderable);
    }

    for(auto container : m_containers) {
        container->iterate(iterator, visited);
    }

    for(auto renderable : m_transRenderables) {
        if(visited.find(renderable) != visited.end()) continue;
        visited.insert(renderable);

        iterator(renderable);
    }
}

}  // namespace Render
}  // namespace Kriti
