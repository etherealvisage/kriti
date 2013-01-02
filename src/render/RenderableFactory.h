#ifndef KRITI_RENDER__RENDERABLE_FACTORY_H
#define KRITI_RENDER__RENDERABLE_FACTORY_H

#include "Renderable.h"
#include "Model.h"

namespace Kriti {
namespace Render {

class RenderableFactory {
public:
    boost::shared_ptr<Renderable> fromModel(boost::shared_ptr<Model> model);
    boost::shared_ptr<Renderable> fromTriangleGeometry(
        const std::vector<Math::Vector> &geometry, std::string technique);
};

}  // namespace Render
}  // namespace Kriti

#endif
