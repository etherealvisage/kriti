#ifndef KRITI_INTERFACE__TEXT_INPUT_H
#define KRITI_INTERFACE__TEXT_INPUT_H

#include <boost/shared_ptr.hpp>

#include <SDL_events.h>

namespace Kriti {
namespace Interface {

class TextInput {
private:
    static boost::shared_ptr<TextInput> s_singleton;
public:
    static boost::shared_ptr<TextInput> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<TextInput>(new TextInput());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    TextInput();
public:
    void begin();
    void end();
private:
    void textEvent(SDL_Event event);
};

}  // namespace Interface
}  // namespace Kriti

#endif
