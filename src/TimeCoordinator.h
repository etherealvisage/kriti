#ifndef KRITI__TIME_COORDINATOR_H
#define KRITI__TIME_COORDINATOR_H

#include <stdint.h>

namespace Kriti {

class TimeCoordinator {
public:
    typedef uint64_t TimeValue;
private:
    static TimeCoordinator *s_singleton;
public:
    static TimeCoordinator *instance() {
        if(!s_singleton) s_singleton = new TimeCoordinator();
        return s_singleton;
    }
    void destroy() {
        delete s_singleton;
    }
private:
    TimeCoordinator() {}
public:
    TimeValue getCurrent();
    TimeValue getForPeriod(int usec);
};

}  // namespace Kriti

#endif
