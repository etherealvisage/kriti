#include <GL/glew.h>

#include "Timer.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace Render {

Timer::Timer() {
    glGenQueries(2, m_qid);
}

Timer::~Timer() {
    glDeleteQueries(2, m_qid);
}

void Timer::begin() {
    glQueryCounter(m_qid[0], GL_TIMESTAMP);
}

void Timer::end() {
    glQueryCounter(m_qid[1], GL_TIMESTAMP);
}

TimeValue Timer::delta() {
    GLint64 t0, t1;
    glGetQueryObjecti64v(m_qid[0], GL_QUERY_RESULT, &t0);
    glGetQueryObjecti64v(m_qid[1], GL_QUERY_RESULT, &t1);

    return TimeValue::fromNsec((t1 - t0));
}

}  // namespace Render
}  // namespace Kriti
