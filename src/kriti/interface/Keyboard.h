#ifndef KRITI_INTERFACE__KEYBOARD_H
#define KRITI_INTERFACE__KEYBOARD_H

#include <string>
#include <boost/signals2.hpp>

#include <SDL.h>

#include "InputDevice.h"
#include "KeyboardRouter.h"

#include "../event/EventQueue.h"

namespace Kriti {
namespace Interface {

class Keyboard : public InputDevice {
private:
    std::map<std::string, int> m_mappings;
    Event::EventQueue *m_queue;
    std::queue<SDL_Event> m_eventQueue;

    std::multimap<int, boost::signals2::signal<void (bool)> *> m_keyMapping;

    KeyboardRouter *m_router;
public:
    Keyboard(Event::EventQueue *queue, KeyboardRouter *router);
    virtual ~Keyboard() {}

    virtual void poll();

    virtual void reloadMapping();

    virtual void handleEvent(SDL_Event *event);
private:
    
};

}  // namespace Interface
}  // namespace Kriti

#endif
