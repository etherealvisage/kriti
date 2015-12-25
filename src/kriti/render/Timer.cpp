#include <GL/glew.h>

#include "Timer.h"
#include "ErrorTracker.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

Timer::Timer() {
    ErrorTracker::trackFrom("Timer constructor (before all)");
    glGenQueries(2, m_qid);
    ErrorTracker::trackFrom("Timer constructor (after gen)");
}

Timer::~Timer() {
    ErrorTracker::trackFrom("Timer destructor (before all)");
    glDeleteQueries(2, m_qid);
    ErrorTracker::trackFrom("Timer destructor (after delete)");
}

void Timer::begin() {
    ErrorTracker::trackFrom("Timer begin (before all)");
    glQueryCounter(m_qid[0], GL_TIMESTAMP);
    ErrorTracker::trackFrom("Timer begin (after query)");
}

void Timer::end() {
    ErrorTracker::trackFrom("Timer end (before all)");
    glQueryCounter(m_qid[1], GL_TIMESTAMP);
    ErrorTracker::trackFrom("Timer end (after query)");
}

TimeValue Timer::delta() {
    GLint64 t0, t1;
    ErrorTracker::trackFrom("Timer delta (before all)");
    glGetQueryObjecti64v(m_qid[0], GL_QUERY_RESULT, &t0);
    ErrorTracker::trackFrom("Timer delta (after query 0)");
    glGetQueryObjecti64v(m_qid[1], GL_QUERY_RESULT, &t1);
    ErrorTracker::trackFrom("Timer delta (after query 1)");

    return TimeValue::fromNsec((t1 - t0));
}

}  // namespace Render
}  // namespace Kriti
