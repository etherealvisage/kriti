#include <SDL.h>

#include "TextInput.h"

#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

boost::shared_ptr<TextInput> TextInput::s_singleton;

TextInput::TextInput() {
    State::Context::addListener(ContextRegistry::instance()->sdlEvent(),
        boost::function<void (SDL_Event)>(
            boost::bind(&TextInput::textEvent, this, _1)));
}

void TextInput::begin() {
    SDL_StartTextInput();
}

void TextInput::end() {
    SDL_StopTextInput();
}

void TextInput::textEvent(SDL_Event event) {
    if(event.type == SDL_TEXTINPUT) {
        ContextRegistry::instance()->fire("text_input",
            boost::make_tuple(std::string(event.text.text)));
    }
}

}  // namespace Interface
}  // namespace Kriti
