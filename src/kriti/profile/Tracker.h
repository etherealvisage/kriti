#ifndef KRITI_PROFILE__TRACKER_H
#define KRITI_PROFILE__TRACKER_H

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "../Globals.h"
#include "../TimeValue.h"

namespace Kriti {

namespace Render {
class Timer;
} // namespace Render

namespace Profile {

class Tracker { KRITI_GLOBAL(Tracker)
private:
    static bool s_enabled;
public:
    static bool enabled() { return s_enabled; }
private:
    std::map<std::string,
        std::pair<bool, std::pair<TimeValue, TimeValue>>> m_timers[2];
    std::map<std::string,
        std::pair<bool, boost::shared_ptr<Render::Timer>>> m_glTimers[2];
    std::map<std::string, int> m_counters[2];

    int m_currentFrame, m_frameCount;
public:
    Tracker();

    void nextFrame();

    void addTimer(std::string name);
    void addGLTimer(std::string name);
    void addCounter(std::string name);

    void beginTimer(std::string name);
    void endTimer(std::string name);
    void beginGLTimer(std::string name);
    void endGLTimer(std::string name);

    void addToCounter(std::string name, int count);
};

}  // namespace Profile
}  // namespace Kriti

#endif
