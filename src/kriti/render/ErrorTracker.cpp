#include <GL/gl.h>
#include <GL/glu.h>

#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

void ErrorTracker::trackFrom(const char *description) {
    auto error = glGetError();
    if(error != GL_NO_ERROR) {
        Message3(Render, Error, "At " << description << ", GL error: "
            << gluErrorString(error));
    }
}

}  // namespace Render
}  // namespace Kriti
