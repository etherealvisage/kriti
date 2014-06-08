#include <GL/glew.h>

#include <SDL.h>

#include "MainMenuContext.h"
#include "Object.h"

#include "context/ContextManager.h"

#include "interface/DeviceManager.h"
#include "interface/Video.h"

#include "render/Model.h"
#include "render/RenderableFactory.h"
#include "render/TextureContext.h"

#include "math/ViewGenerator.h"
#include "math/Constants.h"
#include "math/AffineTransformation.h"

#include "physics/PhysicalObject.h"
#include "physics/WorldRegistry.h"
#include "physics/ObjectFactory.h"

#include "gui/Font.h"
#include "gui/TextRenderer.h"
#include "gui/Scale.h"
#include "gui/PackedLayout.h"
#include "gui/Loader.h"

#include "track/RandomGenerator.h"
#include "track/ClosedSubdivider.h"
#include "track/PlanarExtruder.h"
#include "track/CylindricExtruder.h"

#include "scene/Model.h"

#include "profile/Tracker.h"

#include "ResourceRegistry.h"

#if 0
namespace Kriti {
namespace Game {

boost::shared_ptr<Object> g_exampleObject, g_trackObject;

MainMenuContext::MainMenuContext() {
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::GUI_exit
        ).connect(
            boost::bind(&MainMenuContext::quitMenu, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_playerPitchUp
        ).connect(
            boost::bind(&MainMenuContext::playerPitchUp, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_playerPitchDown
        ).connect(
            boost::bind(&MainMenuContext::playerPitchDown, this, _1)
        );
    m_pipeline = ResourceRegistry::get<Render::Pipeline>("game");
    m_gameStage = ResourceRegistry::get<Render::Stage>("game");

    // camera setup
    m_gameStage->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.1, 1000.0
    ));
    m_gameStage->camera()->step(0.0);

    m_world = Physics::WorldRegistry::instance()->makeWorld();

    m_forceModifier = boost::make_shared<Physics::ObjectForceModifier>();
    m_world->addModifier(m_forceModifier);

    m_playerObject = boost::make_shared<Object>();
    m_playerObject->setRenderable(Render::RenderableFactory().fromModel(
        ResourceRegistry::get<Render::Model>("vehicle4")));

    m_playerObject->setPhysical(
        Physics::ObjectFactory().makeBox(1.0, 1.0, 0.3, 2.0));
    m_playerObject->physical()->moveTo(Math::Vector(0.0, 20.0, -20.0));
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 1.0));

    m_world->addObject(m_playerObject->physical());

    m_gameStage->renderables()->add(m_playerObject->renderable());

    // generate track
    Track::RandomGenerator rg(0);

    auto trackExtrusion = rg.generate(new Track::ClosedSubdivider(4),
        new Track::CylindricExtruder(1, 32));

    auto trackRenderable = Render::RenderableFactory().fromTriangleGeometry(
        trackExtrusion->vertices(), trackExtrusion->normals(), 
        trackExtrusion->texs(), trackExtrusion->indices(), "track");

    m_trackObject = boost::make_shared<Object>();
    m_trackObject->setRenderable(trackRenderable);
    m_trackObject->setPhysical(Physics::ObjectFactory().makeIndexedTriMesh(0.0,
        trackExtrusion->vertices(), trackExtrusion->indices()));

    //m_world->addObject(m_trackObject->physical());

    m_gameStage->renderables()->add(m_trackObject->renderable());

    auto cartwheel_model = ResourceRegistry::get<Scene::Model>("cart_wheel.3ds");
    auto cartwheel_renderable = cartwheel_model->renderable();
    cartwheel_renderable->location() = Math::Vector(0.0, 0.0, -100.0);
    m_gameStage->renderables()->add(cartwheel_renderable);

    m_world->addModifier(m_forceModifier);

    // set up vehicle model
    m_vehicleModel = boost::make_shared<VehicleModel>();
    m_vehicleModel->setRoot(rg.generatedRoot());
    m_vehicle = boost::make_shared<Vehicle>(m_playerObject->physical());
    m_vehicleModel->addVehicle(m_vehicle);

    m_playerObject->physical()->setLinearDamping(0.0);
    m_playerObject->physical()->setAngularDamping(0.0);

    m_world->addModifier(m_vehicleModel);
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 0.0));

    /* set up text/blending pipeline stages. */
    m_guiStage = ResourceRegistry::get<Render::Stage>("gui");
    double aratio = Interface::Video::instance()->aspectRatio();
    m_guiStage->camera()->step(0.0);

    auto font = ResourceRegistry::get<GUI::Font>("ubuntu");

    m_blendStage = ResourceRegistry::get<Render::Stage>("blend");

    m_blendStage->camera()->step(0.0);

    Math::Vector base(-aratio, -1.0), x(aratio*2,0), y(0,2.0);
    m_blendStage->renderables()->add(Render::RenderableFactory().fromQuad(
        base, base+y, base+x+y, base+x, "overlay"));

    Profile::Tracker::instance()->addTimer("Total");
    Profile::Tracker::instance()->addTimer("Rendering");
    Profile::Tracker::instance()->addTimer("Physics");
    Profile::Tracker::instance()->addTimer("GUI updating");
    Profile::Tracker::instance()->addCounter("Triangles");

    m_outlineRegistry = boost::make_shared<GUI::OutlineRegistry>();
    m_mouseInteractor = boost::make_shared<GUI::MouseInteractor>();

    m_guiRoot = GUI::Loader::instance()->guiByName<GUI::Widget>("test");
    Message3(Game, Debug, "m_guiRoot: " << m_guiRoot);

    Interface::DeviceManager::instance()->mouseRouter()->motionSignal(
        ).connect(
            boost::bind(&GUI::MouseInteractor::updateMouseCoordinates,
                m_mouseInteractor.get(), _1, _2)
        );
    Interface::DeviceManager::instance()->mouseRouter()->buttonSignal(
            Interface::MouseRouter::LeftButton
        ).connect(
            boost::bind(&GUI::MouseInteractor::updateMouseButton,
                m_mouseInteractor.get(), 0, _1)
        );
    Interface::DeviceManager::instance()->mouseRouter()->buttonSignal(
            Interface::MouseRouter::MiddleButton
        ).connect(
            boost::bind(&GUI::MouseInteractor::updateMouseButton,
                m_mouseInteractor.get(), 1, _1)
        );
    Interface::DeviceManager::instance()->mouseRouter()->buttonSignal(
            Interface::MouseRouter::RightButton
        ).connect(
            boost::bind(&GUI::MouseInteractor::updateMouseButton,
                m_mouseInteractor.get(), 2, _1)
        );

    m_mouseCursor = boost::make_shared<GUI::MouseCursor>();
    //m_blendStage->addRenderable(m_mouseCursor->renderable());
    m_blendStage->renderables()->addTransparent(m_mouseCursor->renderable());

    Interface::DeviceManager::instance()->mouseRouter()->motionSignal(
        ).connect(
            boost::bind(&GUI::MouseCursor::updateMouseCoordinates,
                m_mouseCursor.get(), _1, _2)
        );
}

void MainMenuContext::run() {
    Profile::Tracker::instance()->nextFrame();
    Profile::Tracker::instance()->beginTimer("Total");

    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    TimeValue interval = TimeValue::fromMsec(1000);
    TimeValue earliest = current - interval;

    m_frames.push(current);
    while(m_frames.size() > 0 && m_frames.front() <= earliest) m_frames.pop();

    {
        Render::Uniforms &u =
            ResourceRegistry::get<Render::Material>(
                "gui_panel")->params();
        u.setParam("gui_xscale", GUI::Scale().xscale());
        u.setParam("gui_yscale", GUI::Scale().yscale());
    }
    {
        Render::Uniforms &u =
            ResourceRegistry::get<Render::Material>(
                "gui_button")->params();
        u.setParam("gui_xscale", GUI::Scale().xscale());
        u.setParam("gui_yscale", GUI::Scale().yscale());
    }

    GUI::Loader::instance()->widgetByName<GUI::Label>("fps-label")->setText(
       StreamAsString() << "FPS: "
           << m_frames.size()/(interval.toMsec()/1000.0)); 
    /*m_fpsLabel->setText(StreamAsString() << "FPS: " <<
        m_frames.size()/(interval.toMsec()/1000.0));*/

    //Message3(Game, Debug, "Main update");

    Profile::Tracker::instance()->beginTimer("GUI updating");
    //m_testPanel->update(m_outlineRegistry,
    /*m_scaler->update(m_outlineRegistry,
        Math::Vector(-2*Interface::Video::instance()->aspectRatio()/3.0, -0.5),
        Math::Vector(1.0, 0.75, 0.0),
        Math::Vector(1.0, 1.0, 1.0));*/

    m_guiRoot->fill(m_guiStage->renderables());
    m_guiRoot->update(m_outlineRegistry,
        Math::Vector(-2*Interface::Video::instance()->aspectRatio()/3.0, -0.5),
        Math::Vector(1.0, 0.75, 0.0),
        Math::Vector(1.0, 1.0, 1.0));

    /*m_scaler->fill(m_guiStage->renderables());

    m_scaler->setFactor(m_scaler->factor() / 1.001); */

    m_mouseInteractor->updateMouseActivation(m_outlineRegistry);
    Profile::Tracker::instance()->endTimer("GUI updating");

    Profile::Tracker::instance()->beginTimer("Physics");
    m_world->step(sinceLast);
    Profile::Tracker::instance()->endTimer("Physics");

    Math::Quaternion q = m_gameStage->camera()->orientation();
    m_gameStage->camera()->setTarget(m_playerObject->renderable()->location()
        + q.conjugate() * Math::Vector(0.0, 0.0, 7.5), q);
    m_gameStage->camera()->step(sinceLast.toUsec() / 1e3);

    Profile::Tracker::instance()->beginTimer("Rendering");
    m_pipeline->render();
    Profile::Tracker::instance()->endTimer("Rendering");

    GLint err = glGetError();
    while(err != GL_NO_ERROR) {
        Message("GL error: " << gluErrorString(err));
        err = glGetError();
    }

    Interface::Video::instance()->swapBuffers();
    // artificially slow down frame rate
    //SDL_Delay(30);
    Profile::Tracker::instance()->endTimer("Total");
}

void MainMenuContext::quitMenu(bool pressed) {
    if(!activated()) return;

    if(pressed) Context::ContextManager::instance()->popContext();
}

void MainMenuContext::playerPitchUp(bool pressed) {
    double amount = 0.5;
    if(!pressed) amount = -amount;

    m_vehicle->setPitch(m_vehicle->pitch() + amount);
}

void MainMenuContext::playerPitchDown(bool pressed) {
    double amount = -0.5;
    if(!pressed) amount = -amount;

    m_vehicle->setPitch(m_vehicle->pitch() + amount);
}

}  // namespace Game
}  // namespace Kriti
#endif
