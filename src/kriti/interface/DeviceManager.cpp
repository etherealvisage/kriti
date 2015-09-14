#include "DeviceManager.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<DeviceManager> DeviceManager::s_singleton;

DeviceManager::DeviceManager() {
    m_queue = new Event::EventQueue();
}

DeviceManager::~DeviceManager() {
    for(auto device : m_deviceList) {
        delete device;
    }
    delete m_keyboardRouter;
}

void DeviceManager::registerDevices() {
    m_keyboardRouter = new KeyboardRouter();
    Keyboard *keyboard = new Keyboard(m_queue, m_keyboardRouter);
    registerDevice(keyboard);
    keyboard->reloadMapping();

    m_mouseRouter = new MouseRouter();
    Mouse *mouse = new Mouse(m_queue, m_mouseRouter);
    registerDevice(mouse);
    mouse->reloadMapping();
}

void DeviceManager::registerDevice(InputDevice *device) {
    m_deviceList.push_back(device);
}

void DeviceManager::pollDevices() {
    for(auto device : m_deviceList) {
        device->poll();
    }
}

void DeviceManager::handleEvent(SDL_Event *event) {
    for(auto device : m_deviceList) {
        device->handleEvent(event);
    }
}

}  // namespace Interface
}  // namespace Kriti
