#ifndef KRITI_GAME__MAIN_MENU_CONTEXT_H
#define KRITI_GAME__MAIN_MENU_CONTEXT_H

#include <boost/shared_ptr.hpp>

#include "context/AbstractContext.h"

#include "render/Model.h"
#include "render/Pipeline.h"

namespace Kriti {
namespace Game {

class MainMenuContext : public Context::AbstractContext {
private:
    boost::shared_ptr<Render::Model> m_simpleModel;
    Render::Pipeline *m_pipeline;
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
