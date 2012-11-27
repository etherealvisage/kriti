#include "Pipeline.h"

#include "math/ViewGenerator.h"

namespace Kriti {
namespace Render {

void Pipeline::addRenderable(boost::shared_ptr<Renderable> renderable) {
    m_objects.push_back(renderable);
}

void Pipeline::render() {
    auto cameraMatrix = m_camera.matrix();

    for(auto renderable : m_objects) {
        renderable->draw(cameraMatrix);
    }
}

}  // namespace Render
}  // namespace Kriti
