#include "../ogl.h"
#include <GL/glu.h>

#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

void ErrorTracker::trackFrom(const char *description) {
    auto error = gl::GetError();
    while(error != gl::NO_ERROR_) {
        Message3(Render, Error, "At " << description << ", GL error: "
            << gluErrorString(error));
        error = gl::GetError();
    }
}

}  // namespace Render
}  // namespace Kriti
