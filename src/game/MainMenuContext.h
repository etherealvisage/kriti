#ifndef KRITI_GAME__MAIN_MENU_CONTEXT_H
#define KRITI_GAME__MAIN_MENU_CONTEXT_H

#include "context/AbstractContext.h"

namespace Kriti {
namespace Game {

class MainMenuContext : public Context::AbstractContext {
public:
    MainMenuContext();

    virtual std::string contextName() { return "Game::MainMenuContext"; }
    
    virtual void run();
private:
    virtual void activateHook() {}
    virtual void deactivateHook() {}
private:
    void quitMenu(bool);
};

}  // namespace Game
}  // namespace Kriti

#endif
