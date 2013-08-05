#include <GL/glew.h>

#include <SDL.h>

#include "MainMenuContext.h"

#include "ResourceRegistry.h"

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
#include "Object.h"

#include "track/RandomGenerator.h"
#include "track/ClosedSubdivider.h"
#include "track/PlanarExtruder.h"

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
            Interface::KeyboardRouter::MM_debugForward
        ).connect(
            boost::bind(&MainMenuContext::debugMoveForward, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_debugBackward
        ).connect(
            boost::bind(&MainMenuContext::debugMoveBackward, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_debugUp
        ).connect(
            boost::bind(&MainMenuContext::debugMoveUp, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_debugDown
        ).connect(
            boost::bind(&MainMenuContext::debugMoveDown, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_debugRLeft
        ).connect(
            boost::bind(&MainMenuContext::debugRotateLeft, this, _1)
        );
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::MM_debugRRight
        ).connect(
            boost::bind(&MainMenuContext::debugRotateRight, this, _1)
        );
    m_pipeline = boost::make_shared<Render::Pipeline>();

    // camera setup
    m_pipeline->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.1, 1000.0
    ));
    m_pipeline->camera()->step(0.0);

    m_world = Physics::WorldRegistry::instance()->makeWorld();

    m_forceModifier = boost::make_shared<Physics::ObjectForceModifier>();
    m_world->addModifier(m_forceModifier);

    m_playerObject = boost::make_shared<Object>();
    m_playerObject->setRenderable(Render::RenderableFactory().fromModel(
        ResourceRegistry::instance()->get<Render::Model>("block")));

    m_playerObject->setPhysical(
        Physics::ObjectFactory().makeBox(1.0, 1.0, 0.3, 2.0));
    m_playerObject->physical()->moveTo(Math::Vector(0.0, 20.0, -20.0));
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 1.0));

    m_world->addObject(m_playerObject->physical());

    m_pipeline->addRenderable(m_playerObject->renderable());

    // generate track
    Track::RandomGenerator rg(3);

    auto trackExtrusion = rg.generate(new Track::ClosedSubdivider(4),
        new Track::PlanarExtruder(8));

    auto trackRenderable = Render::RenderableFactory().fromTriangleGeometry(
        trackExtrusion->vertices(), trackExtrusion->normals(), 
        trackExtrusion->texs(), trackExtrusion->indices(), "track");

    m_trackObject = boost::make_shared<Object>();
    m_trackObject->setRenderable(trackRenderable);
    m_trackObject->setPhysical(Physics::ObjectFactory().makeIndexedTriMesh(0.0,
        trackExtrusion->vertices(), trackExtrusion->indices()));
    m_world->addObject(m_trackObject->physical());

    m_pipeline->addRenderable(m_trackObject->renderable());

    m_world->addModifier(m_forceModifier);

    // set up vehicle model
    m_vehicleModel = boost::make_shared<VehicleModel>();
    m_vehicle = boost::make_shared<Vehicle>(m_playerObject->physical());
    m_vehicleModel->addVehicle(m_vehicle);

    double springK = 0.75;
    double restLength = 1.00;
    m_vehicle->addSuspension(VehicleSuspension(
        Math::Vector(-0.5, -0.30 + Math::Constants::Epsilon, -1.0),
        Math::Vector(-4.0, -10.0, 0.0),
        springK, restLength
    ));
    m_vehicle->addSuspension(VehicleSuspension(
        Math::Vector(0.5, -0.30 + Math::Constants::Epsilon, -1.0),
        Math::Vector(4.0, -10.0, 0.0),
        springK, restLength
    ));
    m_vehicle->addSuspension(VehicleSuspension(
        Math::Vector(-0.5, -0.30 + Math::Constants::Epsilon, 1.0),
        Math::Vector(-4.0, -10.0, 0.0),
        springK, restLength
    ));
    m_vehicle->addSuspension(VehicleSuspension(
        Math::Vector(0.5, -0.30 + Math::Constants::Epsilon, 1.0),
        Math::Vector(4.0, -10.0, 0.0),
        springK, restLength
    ));
    m_playerObject->physical()->setLinearDamping(0.0);
    m_playerObject->physical()->setAngularDamping(0.3);

    m_world->addModifier(m_vehicleModel);
    m_playerObject->physical()->setOrientation(
        Math::Quaternion(Math::Vector(1.0, 0.0, 0.0), 1.0));
}

void MainMenuContext::run() {
    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Math::Quaternion rotation =
        m_playerObject->physical()->orientation().conjugate();

    //Math::Quaternion q = m_pipeline->camera()->orientation()
    Math::Quaternion q = m_playerObject->physical()->orientation().conjugate()
        * Math::Quaternion(Math::Vector(1,0,0), m_rotation.x())
        * Math::Quaternion(Math::Vector(0,1,0), m_rotation.y());

    m_forceModifier->setLinearForce(m_playerObject->physical(),
        q.conjugate()*m_translation/10.0);

    m_world->step(sinceLast);

    m_pipeline->camera()->setTarget(m_playerObject->renderable()->location()
        + q.conjugate() * Math::Vector(0.0, 0.0, 7.5), q);
    m_pipeline->camera()->step(sinceLast.toUsec() / 1e3);
    m_pipeline->render();

    GLint err = glGetError();
    while(err != GL_NO_ERROR) {
        Message("GL error: " << gluErrorString(err));
        err = glGetError();
    }

    Interface::Video::instance()->swapBuffers();
    // artificially slow down frame rate
    //SDL_Delay(30);
}

void MainMenuContext::quitMenu(bool pressed) {
    if(!activated()) return;

    if(pressed) Context::ContextManager::instance()->popContext();
}

void MainMenuContext::debugMoveForward(bool pressed) {
    Math::Vector amount(0.0, 0.0, 5.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugMoveBackward(bool pressed) {
    Math::Vector amount(0.0, 0.0, -4.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugMoveUp(bool pressed) {
    Math::Vector amount(0.0, 25, 0.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugMoveDown(bool pressed) {
    Math::Vector amount(0.0, -15, 0.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugRotateLeft(bool pressed) {
    Math::Vector amount(0.0, -0.05);
    if(!pressed) amount *= -1.0;
    m_rotation = m_rotation + amount;
}

void MainMenuContext::debugRotateRight(bool pressed) {
    Math::Vector amount(0.0, 0.05);
    if(!pressed) amount *= -1.0;
    m_rotation = m_rotation + amount;
}

}  // namespace Game
}  // namespace Kriti
