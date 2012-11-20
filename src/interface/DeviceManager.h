#ifndef KRITI_INTERFACE__DEVICE_MANAGER_H
#define KRITI_INTERFACE__DEVICE_MANAGER_H

#include <vector>

#include "InputDevice.h"
#include "event/EventQueue.h"
#include "KeyboardRouter.h"

namespace Kriti {
namespace Interface {

class DeviceManager {
private:
    static boost::shared_ptr<DeviceManager> s_singleton;
public:
    static boost::shared_ptr<DeviceManager> instance() {
        if(!s_singleton) {
            s_singleton
                = boost::shared_ptr<DeviceManager>(new DeviceManager());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    KeyboardRouter *m_keyboardRouter;
    std::vector<InputDevice *> m_deviceList;
    Event::EventQueue *m_queue;
private:
    DeviceManager();
public:
    ~DeviceManager();
public:
    KeyboardRouter *keyboardRouter() const { return m_keyboardRouter; }

    void registerDevices();
private:
    void registerDevice(InputDevice *device);
public:
    void pollDevices();

    void handleEvent(SDL_Event *event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
