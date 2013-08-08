#include <GL/glew.h> // for GLuint in render/Timer.h

#include "Tracker.h"

#include "config/Tree.h"

#include "render/Timer.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Profile {

boost::shared_ptr<Tracker> Tracker::s_singleton;
bool Tracker::s_enabled = false;

Tracker::Tracker() {
    m_frameCount = 0;
    s_enabled = Config::Tree::instance()->getBool("kriti.profile", false);

    if(s_enabled) {
        Message3(Profile, Log, "Profiling enabled.");
    }
}

void Tracker::nextFrame() {
    if(!enabled()) return;
    // go through old results, and process them.
    Message3(Profile, Log, "Frame #" << m_frameCount << " results:");
    for(auto it : m_timers[m_currentFrame]) {
        if(it.second.first) {
            Message3(Profile, Log, "    - " << it.first << ": "
                << (it.second.second.second - it.second.second.first).toUsec()
                << "us");
        }
        else Message3(Profile, Log, "    - " << it.first << ": N/A");
        it.second.first = false;
    }
    for(auto it : m_glTimers[m_currentFrame]) {
        if(it.second.first) {
            Message3(Profile, Log, "    - " << it.first << ": "
                << it.second.second->delta().toUsec() << "us");
        }
        else Message3(Profile, Log, "    - " << it.first << ": N/A");
        it.second.first = false;
    }

    m_currentFrame = 1-m_currentFrame;
    m_frameCount ++;
}

void Tracker::addTimer(std::string name) {
    if(!enabled()) return;
    m_timers[0][name].first = false;
    m_timers[1][name].first = false;
}

void Tracker::addGLTimer(std::string name) {
    if(!enabled()) return;
    m_glTimers[0][name].first = false;
    m_glTimers[0][name].second = boost::make_shared<Render::Timer>();
    m_glTimers[1][name].first = false;
    m_glTimers[1][name].second = boost::make_shared<Render::Timer>();
}

void Tracker::beginTimer(std::string name) {
    if(!enabled()) return;
    m_timers[m_currentFrame][name].second.first = TimeValue::current();
}

void Tracker::endTimer(std::string name) {
    if(!enabled()) return;
    m_timers[m_currentFrame][name].first = true;
    m_timers[m_currentFrame][name].second.second = TimeValue::current();
}

void Tracker::beginGLTimer(std::string name) {
    if(!enabled()) return;
    m_glTimers[m_currentFrame][name].second->begin();
}

void Tracker::endGLTimer(std::string name) {
    if(!enabled()) return;
    m_glTimers[m_currentFrame][name].first = true;
    m_glTimers[m_currentFrame][name].second->end();
}

}  // namespace Profile
}  // namespace Kriti
