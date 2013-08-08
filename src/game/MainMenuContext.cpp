#include <GL/glew.h>

#include <SDL.h>

#include "MainMenuContext.h"
#include "Object.h"


#include "context/ContextManager.h"

#include "interface/DeviceManager.h"
#include "interface/Video.h"

#include "render/Model.h"
#include "render/RenderableFactory.h"

#include "math/ViewGenerator.h"
#include "math/Constants.h"
#include "math/AffineTransformation.h"

#include "physics/PhysicalObject.h"
#include "physics/WorldRegistry.h"
#include "physics/ObjectFactory.h"

#include "gui/Font.h"
#include "gui/TextRenderer.h"

#include "track/RandomGenerator.h"
#include "track/ClosedSubdivider.h"
#include "track/PlanarExtruder.h"
#include "track/CylindricExtruder.h"

#include "profile/Tracker.h"

#include "ResourceRegistry.h"

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
    m_pipeline = boost::make_shared<Render::Pipeline>();
    m_gameStage = boost::make_shared<Render::Stage>("Game stage");

    m_pipeline->setLastStage(m_gameStage);

    // camera setup
    Message3(Game, Debug, "Aspect ratio: " << Interface::Video::instance()->aspectRatio());
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
        ResourceRegistry::instance()->get<Render::Model>("vehicle4")));

    m_playerObject->setPhysical(
        Physics::ObjectFactory().makeBox(1.0, 1.0, 0.3, 2.0));
    m_playerObject->physical()->moveTo(Math::Vector(0.0, 20.0, -20.0));
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 1.0));

    m_world->addObject(m_playerObject->physical());

    m_gameStage->addRenderable(m_playerObject->renderable());

    // generate track
    Track::RandomGenerator rg(3);

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

    m_gameStage->addRenderable(m_trackObject->renderable());

    m_world->addModifier(m_forceModifier);

    // set up vehicle model
    m_vehicleModel = boost::make_shared<VehicleModel>();
    m_vehicleModel->setRoot(rg.generatedRoot());
    m_vehicle = boost::make_shared<Vehicle>(m_playerObject->physical());
    //m_vehicleModel->addVehicle(m_vehicle);

    m_playerObject->physical()->setLinearDamping(0.0);
    m_playerObject->physical()->setAngularDamping(0.0);

    m_world->addModifier(m_vehicleModel);
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 0.0));

    /* set up text/blending pipeline stages. */
    m_textStage = boost::make_shared<Render::Stage>("Text stage");
    double aratio = Interface::Video::instance()->aspectRatio();
    m_textStage->camera()->setProjection(Math::ViewGenerator().orthogonal(
        aratio, 2.0, 0.1, 1000.0
    ));
    m_textStage->camera()->step(0.0);

    auto font = ResourceRegistry::instance()->get<GUI::Font>("ubuntu");
    //auto text = GUI::TextRenderer().render(font, "Hello, World!");

    //m_textStage->addRenderable(text);
    /*{
        Math::Vector base(-aratio/2, -1.0), x(aratio,0), y(0,2.0);
        m_textStage->addRenderable(Render::RenderableFactory().fromQuad(
            base, base+y, base+x+y, base+x, "ubuntu"));
    }*/
    
    /*m_textStage->addRenderable(Render::RenderableFactory().fromQuad(
        Math::Vector(0.0113516,0.11792,0),
        Math::Vector(0.132445,0.11792,0),
        Math::Vector(0.228148,0.11792,0),
        Math::Vector(0.107055,0.11792,0), "red"));*/

    m_blendStage = boost::make_shared<Render::Stage>("Blending stage");
    m_blendStage->addPrevious(m_gameStage);
    m_blendStage->addPrevious(m_textStage);

    m_blendStage->addMapping(0, Render::Framebuffer::ColourBuffer0, "baseStage");
    m_blendStage->addMapping(1, Render::Framebuffer::ColourBuffer0, "overlayStage");

    m_blendStage->camera()->setProjection(Math::ViewGenerator().orthogonal(
        aratio, 2.0, 0.1, 1000.0
    ));
    m_blendStage->camera()->step(0.0);

    Math::Vector base(-aratio/2, -1.0), x(aratio,0), y(0,2.0);
    m_blendStage->addRenderable(Render::RenderableFactory().fromQuad(
        base, base+y, base+x+y, base+x, "overlay"));

    m_pipeline->setLastStage(m_blendStage);

    Profile::Tracker::instance()->addTimer("Total");
    Profile::Tracker::instance()->addTimer("Physics");
}

void MainMenuContext::run() {
    Profile::Tracker::instance()->nextFrame();
    Profile::Tracker::instance()->beginTimer("Total");

    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    TimeValue fiveAgo = current - TimeValue::fromMsec(5000);

    m_frames.push(current);
    while(m_frames.size() > 0 && m_frames.front() <= fiveAgo) m_frames.pop();
    if(m_fpsDisplay) m_textStage->removeRenderable(m_fpsDisplay);
    if(m_frames.size() > 1) {
        m_fpsDisplay = GUI::TextRenderer().render(
            ResourceRegistry::instance()->get<GUI::Font>("ubuntu"),
            StreamAsString() << "FPS: " <<
                m_frames.size()/((current - m_frames.front()).toMsec()/1000.0)
        );
        m_fpsDisplay->scale() = 0.25;
        m_fpsDisplay->location() = Math::Vector(
            -Interface::Video::instance()->aspectRatio()/2.0, -1.0);
        m_textStage->addRenderable(m_fpsDisplay);
    }

    Math::Quaternion q = m_gameStage->camera()->orientation();

    Profile::Tracker::instance()->beginTimer("Physics");
    m_world->step(sinceLast);
    Profile::Tracker::instance()->endTimer("Physics");

    m_gameStage->camera()->setTarget(m_playerObject->renderable()->location()
        + q.conjugate() * Math::Vector(0.0, 0.0, 7.5), q);
    m_gameStage->camera()->step(sinceLast.toUsec() / 1e3);
    m_pipeline->render();

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
