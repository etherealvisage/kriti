#ifndef KRITI_RENDER__SCENE_H
#define KRITI_RENDER__SCENE_H

#include "Pipeline.h"
#include "SceneCamera.h"

namespace Kriti {
namespace Render {

// Scene management class.
class Scene {
private:
    SceneCamera *m_camera;
    Pipeline *m_pipeline;
public:
    Scene();
    ~Scene();

    SceneCamera *camera() const { return m_camera; }
};

}  // namespace Render
}  // namespace Kriti

#endif
