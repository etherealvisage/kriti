#include <GL/glew.h>

#include "MainMenuContext.h"

#include "SDL.h"

#include "ResourceRegistry.h"

#include "context/ContextManager.h"
#include "interface/DeviceManager.h"
#include "interface/Video.h"
#include "render/Model.h"
#include "render/RenderableFactory.h"
#include "math/ViewGenerator.h"
#include "math/Constants.h"
#include "math/AffineTransformation.h"
#include "physics/BulletWrapper.h"
#include "physics/PhysicalObject.h"
#include "Object.h"

#include "track/RandomGenerator.h"
#include "track/ClosedSubdivider.h"
#include "track/PlanarExtruder.h"

namespace Kriti {
namespace Game {

boost::shared_ptr<Object> g_exampleObject;

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
    m_pipeline = new Render::Pipeline();

    m_pipeline->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.01, 1000.0
    ));

    m_pipeline->camera()->setTarget(Math::Vector(), Math::Quaternion());
    m_pipeline->camera()->step(0.0);

    boost::shared_ptr<Render::Renderable> simpleRenderable(
        Render::RenderableFactory().fromModel(
            ResourceRegistry::instance()->get<Render::Model>("simple")));

    boost::shared_ptr<Physics::PhysicalObject> simplePhysical(
        Physics::PhysicalObject::fromSphere(1.0, 1.0));

    simplePhysical->setLocation(Math::Vector(0.0, 0.0, -20.0));

    m_pipeline->addRenderable(simpleRenderable);

    g_exampleObject = boost::shared_ptr<Object>(new Object());
    g_exampleObject->setRenderable(simpleRenderable);
    g_exampleObject->setPhysical(simplePhysical);

    /*Game::Track gt;
    gt.generateTrack();

    auto trackRenderable = Render::RenderableFactory().fromTriangleGeometry(
        gt.geometry(), "simple");

    trackRenderable->location() = Math::Vector(0.0, -2.0, -0.0);

    m_pipeline->addRenderable(trackRenderable);*/

    Track::RandomGenerator rg(1);
    rg.generate(
        new Track::ClosedSubdivider(4),
        new Track::PlanarExtruder(2.5)
    );

    std::vector<Math::Vector> vertices, normals;
    std::vector<unsigned int> tris;
    rg.getExtrusion(vertices, normals, tris);

    auto trackRenderable = Render::RenderableFactory().fromTriangleGeometry(
        vertices, normals, tris, "simple");

    trackRenderable->location() = Math::Vector(0.0, -20.0, 0.0);

    m_pipeline->addRenderable(trackRenderable);
}

void MainMenuContext::run() {
    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    //Message3(General, Log, "Time since last frame: " << sinceLast.toUsec());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Physics::BulletWrapper::instance()->stepWorld(sinceLast.toUsec());
    g_exampleObject->updateRenderableFromPhysical();
    //Message("Y coordinate: " << g_exampleObject->physical()->location().y());

    m_pipeline->camera()->step(sinceLast.toUsec() / 1e3);

    m_pipeline->camera()->setTarget(
        m_pipeline->camera()->position() + m_translation,
        m_pipeline->camera()->orientation());

    m_pipeline->render();

    GLint err = glGetError();
    while(err != GL_NO_ERROR) {
        Message("GL error: " << gluErrorString(err));
        err = glGetError();
    }

    SDL_GL_SwapBuffers();
    // artificially slow down frame rate
    //SDL_Delay(30);
}

void MainMenuContext::quitMenu(bool) {
    if(!activated()) return;

    Context::ContextManager::instance()->popContext();
}

void MainMenuContext::debugMoveForward(bool pressed) {
    Math::Vector amount(0.0, 0.0, 2.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugMoveBackward(bool pressed) {
    Math::Vector amount(0.0, 0.0, -1.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

}  // namespace Game
}  // namespace Kriti
