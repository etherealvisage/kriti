#include "MainMenuContext.h"

#include "SDL.h"

#include "context/ContextManager.h"
#include "interface/DeviceManager.h"

namespace Kriti {
namespace Game {

MainMenuContext::MainMenuContext() {
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::GUI_exit
        ).connect(
            boost::bind(&MainMenuContext::quitMenu, this, _1)
        );
}

void MainMenuContext::run() {
    SDL_Delay(30);
}

void MainMenuContext::quitMenu(bool) {
    if(!activated()) return;

    Context::ContextManager::instance()->popContext();
}

}  // namespace Game
}  // namespace Kriti
