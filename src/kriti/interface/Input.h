#ifndef KRITI_INTERFACE__INPUT_H
#define KRITI_INTERFACE__INPUT_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "Keyboard.h"
#include "Mouse.h"

namespace Kriti {
namespace Interface {

class Input {
private:
    static boost::shared_ptr<Input> s_singleton;
public:
    static boost::shared_ptr<Input> instance() {
        if(!s_singleton) {
            s_singleton = boost::make_shared<Input>();
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    Keyboard *m_keyboard;
    Mouse *m_mouse;
public:
    Input();
    ~Input();
};

}  // namespace Interface
}  // namespace Kriti

#endif
