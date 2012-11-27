#ifndef KRITI_RENDER__PIPELINE_H
#define KRITI_RENDER__PIPELINE_H

#include <vector>

#include "Renderable.h"
#include "SceneCamera.h"

namespace Kriti {
namespace Render {

class Pipeline {
private:
    std::vector<boost::shared_ptr<Renderable>> m_objects;
    SceneCamera m_camera;
public:
    SceneCamera *camera() { return &m_camera; }

    void addRenderable(boost::shared_ptr<Renderable> renderable);

    void render();
};

}  // namespace Render
}  // namespace Kriti

#endif
