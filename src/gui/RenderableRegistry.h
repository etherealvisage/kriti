#ifndef KRITI_GUI__RENDERABLE_REGISTRY_H
#define KRITI_GUI__RENDERABLE_REGISTRY_H

#include <set>

#include <boost/function.hpp>

#include "render/Renderable.h"

namespace Kriti {
namespace GUI {

class RenderableRegistry {
public:
    typedef boost::function<void (boost::shared_ptr<Render::Renderable>)>
        FunctionType;
private:
    std::set<boost::shared_ptr<Render::Renderable>> m_renderables;
public:
    void add(boost::shared_ptr<Render::Renderable> renderable)
        { m_renderables.insert(renderable); }
    void remove(boost::shared_ptr<Render::Renderable> renderable)
        { m_renderables.erase(m_renderables.find(renderable)); }

    void iterate(FunctionType function);
};

}  // namespace GUI
}  // namespace Kriti

#endif
