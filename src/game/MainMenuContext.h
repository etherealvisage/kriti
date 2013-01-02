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

    Math::Vector m_rotation;
    Math::Vector m_translation;
public:
    MainMenuContext();

    virtual std::string contextName() { return "Game::MainMenuContext"; }
    
    virtual void run();
private:
    virtual void activateHook() { m_lastTime = TimeValue::current(); }
    virtual void deactivateHook() {}
private:
    void quitMenu(bool);

    void debugMoveForward(bool pressed);
    void debugMoveBackward(bool pressed);
    void debugMoveUp(bool pressed);
    void debugMoveDown(bool pressed);
    void debugRotateLeft(bool pressed);
    void debugRotateRight(bool pressed);
};

}  // namespace Game
}  // namespace Kriti

#endif
