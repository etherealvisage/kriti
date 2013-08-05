#ifndef KRITI_GAME__MAIN_MENU_CONTEXT_H
#define KRITI_GAME__MAIN_MENU_CONTEXT_H

#include <boost/shared_ptr.hpp>

#include "context/AbstractContext.h"

#include "Object.h"
#include "VehicleModel.h"

#include "render/Model.h"
#include "render/Pipeline.h"
#include "render/Renderable.h"

#include "physics/World.h"
#include "physics/ObjectForceModifier.h"

#include "TimeValue.h"

namespace Kriti {
namespace Game {

class MainMenuContext : public Context::AbstractContext {
private:
    boost::shared_ptr<Render::Pipeline> m_pipeline;
    boost::shared_ptr<Render::Stage> m_gameStage;
    boost::shared_ptr<Physics::World> m_world;
    boost::shared_ptr<Physics::ObjectForceModifier> m_forceModifier;
    boost::shared_ptr<Object> m_playerObject, m_trackObject;
    boost::shared_ptr<Vehicle> m_vehicle;
    boost::shared_ptr<VehicleModel> m_vehicleModel;
    TimeValue m_lastTime;
public:
    MainMenuContext();

    virtual std::string contextName() { return "Game::MainMenuContext"; }
    
    virtual void run();
private:
    virtual void activateHook() { m_lastTime = TimeValue::current(); }
    virtual void deactivateHook() {}
private:
    void quitMenu(bool pressed);

    void playerPitchUp(bool pressed);
    void playerPitchDown(bool pressed);
};

}  // namespace Game
}  // namespace Kriti

#endif
