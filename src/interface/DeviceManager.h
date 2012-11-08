#ifndef KRITI_INTERFACE__DEVICE_MANAGER_H
#define KRITI_INTERFACE__DEVICE_MANAGER_H

#include <vector>

#include "InputDevice.h"
#include "event/EventQueue.h"

namespace Kriti {
namespace Interface {

class DeviceManager {
private:
    static DeviceManager *s_singleton;
public:
    static DeviceManager *instance() {
        if(!s_singleton) {
            s_singleton = new DeviceManager();
        }
        return s_singleton;
    }
    static void destroy() {
        delete s_singleton;
    }
private:
    std::vector<InputDevice *> m_deviceList;
    Event::EventQueue *m_queue;
private:
    DeviceManager();
    ~DeviceManager();
public:
    template<typename DeviceType>
    void registerDevice();
private:
    void registerDevice(InputDevice *device);
public:
    void pollDevices();

    void handleEvent(SDL_Event *event);
};

template<typename DeviceType>
void DeviceManager::registerDevice() {
    registerDevice(new DeviceType(m_queue));
}

}  // namespace Interface
}  // namespace Kriti

#endif
