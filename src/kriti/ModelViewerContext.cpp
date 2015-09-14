#include <boost/make_shared.hpp>

#include "ModelViewerContext.h"

#include "context/ContextManager.h"

#include "interface/DeviceManager.h"
#include "interface/Video.h"

#include "math/ViewGenerator.h"

#include "scene/Model.h"
#include "scene/LightRegistry.h"

#include "ResourceRegistry.h"

namespace Kriti {

ModelViewerContext::ModelViewerContext() {
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::GUI_exit
        ).connect(
            boost::bind(&ModelViewerContext::quitMenu, this, _1)
        );

    m_pipeline = ResourceRegistry::get<Render::Pipeline>("model");
    m_modelStage = ResourceRegistry::get<Render::Stage>("model");


    // camera setup
    m_camera = boost::make_shared<Scene::Camera>();
    m_camera->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.1, 1000.0
    ));
    m_modelStage->addUniformHook(m_camera);

    auto cartwheel_model = ResourceRegistry::get<Scene::Model>("vehicle-2.3ds");
    auto cartwheel_renderable = cartwheel_model->renderable();
    cartwheel_renderable->location() = Math::Vector(0.0, 0.0, 0.0);
    m_modelStage->renderables()->add(cartwheel_renderable);

    auto lightRegistry = boost::make_shared<Scene::LightRegistry>();
    lightRegistry->setCamera(m_camera);

    lightRegistry->add(boost::make_shared<Scene::Light>(
        Math::Vector(3.0,0.0,0.0),
        Math::Vector(1.0,1.0,1.0),
        Math::Vector(1.0,1.0,1.0),
        1.0,1.0,1.0));
    /*lightRegistry->add(boost::make_shared<Scene::Light>(
        Math::Vector(0.0,-100.0,0.0),
        Math::Vector(1.0,1.0,1.0),
        Math::Vector(1.0,1.0,1.0),
        1.0,1.0,1.0));*/
    m_modelStage->addUniformHook(lightRegistry);
}

void ModelViewerContext::run() {
    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    Math::Quaternion q = m_camera->orientation();
    q = q * Math::Quaternion(Math::Vector(0.0, 1.0, 0.0), M_PI/100.0);
    m_camera->setTarget(
        q.conjugate() * Math::Vector(0.0, 0.0, 10.0), q);
    m_camera->step(sinceLast.toUsec() / 1e3);
    
    m_pipeline->render();
    
    Interface::Video::instance()->swapBuffers();
}

void ModelViewerContext::quitMenu(bool pressed) {
    if(!activated()) return;

    if(pressed) Context::ContextManager::instance()->popContext();
}

}  // namespace Kriti
