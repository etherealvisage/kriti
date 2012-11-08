#include "DeviceManager.h"

namespace Kriti {
namespace Interface {

DeviceManager *DeviceManager::s_singleton;

DeviceManager::DeviceManager() {
    m_queue = new Event::EventQueue();
}

DeviceManager::~DeviceManager() {
    for(auto device : m_deviceList) {
        delete device;
    }
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
