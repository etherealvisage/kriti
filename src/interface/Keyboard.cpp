#include <cctype>

#include "Keyboard.h"
#include "config/Tree.h"

namespace Kriti {
namespace Interface {

Keyboard::Keyboard(Event::EventQueue *queue, KeyboardRouter *router)
    : m_queue(queue), m_router(router) {

    for(int i = 0; i <= SDLK_LAST; i ++) {
        if(std::islower(i) || std::isdigit(i)) {
            m_mappings[StreamAsString() << (char)i] = i;
        }
    }
    m_mappings["escape"] = SDLK_ESCAPE;
}

void Keyboard::poll() {
    while(m_eventQueue.size() > 0) {
        auto event = m_eventQueue.front();
        m_eventQueue.pop();

        //auto signal = m_keyMapping[event.key.keysym.sym];
        auto iterator = m_keyMapping.find(event.key.keysym.sym);
        while(iterator != m_keyMapping.end() &&
            iterator->first == event.key.keysym.sym) {

            m_router->fire(*iterator->second, event.type == SDL_KEYDOWN);
            
            ++iterator;
        }
        // fire the signal if it is mapped.
        //if(signal != NULL) {
            //Event::EventRouter::fire(*signal, event.type == SDL_KEYDOWN);
        //}
    }
}

void Keyboard::reloadMapping() {
    m_keyMapping.clear();

    boost::shared_ptr<Config::Tree> tree = Config::Tree::instance();
    KeyboardRouter::SignalName name =
        static_cast<KeyboardRouter::SignalName>(0);
    const char *p;
    while((p = m_router->configName(name)) != NULL) {
        std::string key = tree->getString(StreamAsString() << "keys." << p);

        int keycode = m_mappings[key];
        m_keyMapping.insert(std::make_pair(keycode, &m_router->signal(name)));

        name = static_cast<KeyboardRouter::SignalName>(
            static_cast<int>(name)+1);
    }
}

void Keyboard::handleEvent(SDL_Event *event) {
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
        m_eventQueue.push(*event);
    }
}

}  // namespace Interface
}  // namespace Kriti
