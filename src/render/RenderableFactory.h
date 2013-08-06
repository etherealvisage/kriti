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
        const std::vector<Math::Vector> &vertices,
        const std::vector<Math::Vector> &normals,
        const std::vector<unsigned int> &tris, std::string technique);
    boost::shared_ptr<Renderable> fromTriangleGeometry(
        const std::vector<Math::Vector> &vertices,
        const std::vector<Math::Vector> &normals,
        const std::vector<Math::Vector> &texs,
        const std::vector<unsigned int> &tris, std::string technique);
    boost::shared_ptr<Renderable> fromLineGeometry(
        const std::vector<Math::Vector> &vertices, std::string technique);

    // winding order is CCW, so p1/p2/p3/p4 get texture coordinates
    // (0,0), (0,1), (1,1), and (1,0) respectively.
    boost::shared_ptr<Renderable> fromQuad(
        Math::Vector p1, Math::Vector p2, Math::Vector p3, Math::Vector p4,
        std::string technique);
};

}  // namespace Render
}  // namespace Kriti

#endif
