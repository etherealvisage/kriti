#include <SDL.h>

#include "TextInput.h"

#include "ContextRegistry.h"

namespace Kriti {
namespace Interface {

TextInput::TextInput() {
    State::Context::addListener(ContextRegistry::get()->sdlEvent(),
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
        ContextRegistry::get()->fire("textInput",
            boost::make_tuple(std::string(event.text.text)));
    }
}

}  // namespace Interface
}  // namespace Kriti
