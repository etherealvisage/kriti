#ifndef KRITI_GAME__MAIN_MENU_CONTEXT_H
#define KRITI_GAME__MAIN_MENU_CONTEXT_H

#include <boost/shared_ptr.hpp>

#include "context/AbstractContext.h"

#include "render/Model.h"
#include "render/Pipeline.h"
#include "render/Renderable.h"

#include "TimeValue.h"

namespace Kriti {
namespace Game {

class MainMenuContext : public Context::AbstractContext {
private:
    Render::Pipeline *m_pipeline;
    TimeValue m_lastTime;
public:
    MainMenuContext();

    virtual std::string contextName() { return "Game::MainMenuContext"; }
    
    virtual void run();
private:
    virtual void activateHook() { m_lastTime = TimeValue::current(); }
    virtual void deactivateHook() {}
private:
    void quitMenu(bool);
};

}  // namespace Game
}  // namespace Kriti

#endif
