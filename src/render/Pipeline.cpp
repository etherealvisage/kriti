#include <GL/glew.h>

#include "Pipeline.h"

#include "MessageSystem.h"

#include "math/ViewGenerator.h"

namespace Kriti {
namespace Render {

void Pipeline::addRenderable(boost::shared_ptr<Renderable> renderable) {
    m_objects.push_back(renderable);
}

void Pipeline::render() {
    auto cameraMatrix = m_camera.matrix();

    for(auto renderable : m_objects) {
        auto error = glGetError();
        if(error != GL_NO_ERROR) {
            Message3(Render, Error, "GL error: " << gluErrorString(error));
        }
        renderable->draw(cameraMatrix);
    }
}

}  // namespace Render
}  // namespace Kriti
