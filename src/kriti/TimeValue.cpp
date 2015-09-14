#include <time.h>

#include "TimeValue.h"

namespace Kriti {

TimeValue TimeValue::current() {
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);

    return current.tv_nsec + current.tv_sec*1000000000;
}

}  // namespace Kriti
