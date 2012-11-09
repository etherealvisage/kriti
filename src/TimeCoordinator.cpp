#include <time.h>

#include "TimeCoordinator.h"

namespace Kriti {

TimeCoordinator *TimeCoordinator::s_singleton;

TimeCoordinator::TimeValue TimeCoordinator::getCurrent() {
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);

    return current.tv_nsec + current.tv_sec*1000000000;
}

TimeCoordinator::TimeValue TimeCoordinator::getForPeriod(int usec) {
    return usec * 1000;
}

}  // namespace Kriti
