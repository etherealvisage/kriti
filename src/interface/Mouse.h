#ifndef KRITI_INTERFACE__MOUSE_H
#define KRITI_INTERFACE__MOUSE_H

#include <queue>

#include "InputDevice.h"
#include "MouseRouter.h"
#include "event/EventQueue.h"

namespace Kriti {
namespace Interface {

class Mouse : public InputDevice {
private:
    Event::EventQueue *m_queue;
    std::queue<SDL_Event> m_eventQueue;
    MouseRouter *m_router;
public:
    Mouse(Event::EventQueue *queue, MouseRouter *router) : m_queue(queue),
        m_router(router) {}
    virtual ~Mouse() {}

    virtual void poll();

    /// mouse has no mapping to reload...
    virtual void reloadMapping() {}

    virtual void handleEvent(SDL_Event *event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
