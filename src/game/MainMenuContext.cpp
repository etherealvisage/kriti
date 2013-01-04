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

boost::shared_ptr<Object> g_exampleObject, g_trackObject;
boost::shared_ptr<Physics::ObjectManipulator> g_exampleManipulator;

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
    m_pipeline = new Render::Pipeline();

    m_pipeline->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.01, 1000.0
    ));

    m_pipeline->camera()->setTarget(Math::Vector(), Math::Quaternion());
    m_pipeline->camera()->step(0.0);

    boost::shared_ptr<Render::Renderable> simpleRenderable(
        Render::RenderableFactory().fromModel(
            ResourceRegistry::instance()->get<Render::Model>("ball")));

    boost::shared_ptr<Physics::PhysicalObject> simplePhysical(
        Physics::PhysicalObject::fromSphere(1.0, 1.0));

    simplePhysical->setLocation(Math::Vector(0.0, 20.0, -60.0));

    m_pipeline->addRenderable(simpleRenderable);

    g_exampleObject = boost::shared_ptr<Object>(new Object());
    g_exampleObject->setRenderable(simpleRenderable);
    g_exampleObject->setPhysical(simplePhysical);

    g_exampleManipulator =
        boost::make_shared<Physics::ObjectManipulator>(simplePhysical);

    Physics::BulletWrapper::instance()->addObjectManipulator(
        g_exampleManipulator);

    Track::RandomGenerator rg(3);
    auto trackExtrusion = rg.generate(
        new Track::ClosedSubdivider(4),
        new Track::PlanarExtruder(7.5)
    );

    auto trackRenderable = Render::RenderableFactory().fromTriangleGeometry(
        trackExtrusion->vertices(), trackExtrusion->normals(), 
        trackExtrusion->texs(), trackExtrusion->indices(), "track");

    boost::shared_ptr<Physics::PhysicalObject> trackPhysical(
        Physics::PhysicalObject::fromTriGeometry(0.0,
            trackExtrusion->vertices(), trackExtrusion->indices()));

    m_pipeline->addRenderable(trackRenderable);

    g_trackObject = boost::make_shared<Object>();
    g_trackObject->setRenderable(trackRenderable);
    g_trackObject->setPhysical(trackPhysical);

    auto r = Physics::BulletWrapper::instance()->debugRenderable();

    m_pipeline->addRenderable(r);
    Physics::BulletWrapper::instance()->updateDebugRenderable();

#if 0
    if(0) {
        std::vector<Math::Vector> nlv;
        for(unsigned i = 0; i < tris.size(); i += 3) {
            auto v1 = vertices[tris[i]];
            auto v2 = vertices[tris[i+1]];
            auto v3 = vertices[tris[i+2]];
            auto centre = (v1+v2+v3)/3;
            auto normal1 = normals[tris[i]];
            nlv.push_back(centre);
            nlv.push_back(centre + normal1);
            auto normal2 = normals[tris[i+1]];
            nlv.push_back(centre);
            nlv.push_back(centre + normal2);
            auto normal3 = normals[tris[i+2]];
            nlv.push_back(centre);
            nlv.push_back(centre + normal3);
        }
        auto trackNormalsRenderable =
            Render::RenderableFactory().fromLineGeometry(nlv, "red");

        m_pipeline->addRenderable(trackNormalsRenderable);
    }
#endif
}

void MainMenuContext::run() {
    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    //Message3(General, Log, "Time since last frame: " << sinceLast.toUsec());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    g_exampleManipulator->setLinearForce(m_translation);

    Physics::BulletWrapper::instance()->stepWorld(sinceLast.toUsec());
    g_exampleObject->updateRenderableFromPhysical();
    g_trackObject->updateRenderableFromPhysical();
    //Message("Y coordinate: " << g_exampleObject->physical()->location().y());
    if(g_exampleObject->physical()->location().y() < -100) {
        g_exampleObject->physical()->setLocation(
            Math::Vector(0.0, 20.0, -20.0));
    }

    m_pipeline->camera()->step(sinceLast.toUsec() / 1e3);

    Math::Quaternion orientation = m_pipeline->camera()->orientation()
            * Math::Quaternion(Math::Vector(1.0, 0.0, 0.0),m_rotation.x())
            * Math::Quaternion(Math::Vector(0.0, 1.0, 0.0),m_rotation.y());
    m_pipeline->camera()->setTarget(-g_exampleObject->physical()->location()
        + orientation.conjugate() * Math::Vector(0.0, 0.0, -5.0),
        orientation);

    //Physics::BulletWrapper::instance()->updateDebugRenderable();

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

void MainMenuContext::quitMenu(bool pressed) {
    if(!activated()) return;

    if(pressed) Context::ContextManager::instance()->popContext();
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

void MainMenuContext::debugMoveUp(bool pressed) {
    Math::Vector amount(0.0, 0.4, 0.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugMoveDown(bool pressed) {
    Math::Vector amount(0.0, -0.4, 0.0);
    if(!pressed) amount *= -1.0;
    m_translation = m_translation + amount;
}

void MainMenuContext::debugRotateLeft(bool pressed) {
    Math::Vector amount(0.0, -0.1);
    if(!pressed) amount *= -1.0;
    m_rotation = m_rotation + amount;
}

void MainMenuContext::debugRotateRight(bool pressed) {
    Math::Vector amount(0.0, 0.1);
    if(!pressed) amount *= -1.0;
    m_rotation = m_rotation + amount;
}

}  // namespace Game
}  // namespace Kriti
