#ifndef KRITI_INTERFACE__KEYBOARD_H
#define KRITI_INTERFACE__KEYBOARD_H

#include <boost/signal.hpp>

#include "SDL.h"

#include "InputDevice.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"

namespace Kriti {
namespace Interface {

class Keyboard : public InputDevice {
private:
    Event::EventQueue *m_queue;
    std::queue<SDL_Event> m_eventQueue;
    std::map<int, boost::signal<void (bool)> *> m_keyMapping;
public:
    Keyboard(Event::EventQueue *queue) : m_queue(queue) {}
    virtual ~Keyboard() {}

    virtual void poll();

    virtual void reloadMapping();

    virtual void handleEvent(SDL_Event *event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
