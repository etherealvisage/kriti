#ifndef KRITI_RENDER__ERROR_TRACKER_H
#define KRITI_RENDER__ERROR_TRACKER_H

namespace Kriti {
namespace Render {

class ErrorTracker {
public:
    static void trackFrom(const char *description);
};

}  // namespace Render
}  // namespace Kriti

#endif
