#ifndef KRITI_RENDER__TIMER_H
#define KRITI_RENDER__TIMER_H

#include "TimeValue.h"

namespace Kriti {
namespace Render {

class Timer {
private:
    GLuint m_qid[2];
public:
    Timer();
    ~Timer();

    void begin();
    void end();

    TimeValue delta();
};

}  // namespace Render
}  // namespace Kriti

#endif
