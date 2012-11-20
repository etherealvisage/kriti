#include "Scene.h"

namespace Kriti {
namespace Render {

Scene::Scene() {
    m_camera = new SceneCamera();

    m_pipeline = new Pipeline();
}

}  // namespace Render
}  // namespace Kriti
