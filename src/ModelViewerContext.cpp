#include "ModelViewerContext.h"

#include "context/ContextManager.h"

#include "interface/DeviceManager.h"
#include "interface/Video.h"

#include "math/ViewGenerator.h"

#include "scene/Model.h"

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
    m_modelStage->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, Interface::Video::instance()->aspectRatio(),
        0.1, 1000.0
    ));

    auto cartwheel_model = ResourceRegistry::get<Scene::Model>("cart_wheel.3ds");
    auto cartwheel_renderable = cartwheel_model->renderable();
    cartwheel_renderable->location() = Math::Vector(0.0, 0.0, 0.0);
    m_modelStage->renderables()->add(cartwheel_renderable);
}

void ModelViewerContext::run() {
    TimeValue current = TimeValue::current();
    TimeValue sinceLast = current - m_lastTime;
    m_lastTime = current;

    Math::Quaternion q = m_modelStage->camera()->orientation();
    q = q * Math::Quaternion(Math::Vector(0.0, 1.0, 0.0), M_PI/100.0);
    m_modelStage->camera()->setTarget(
        q.conjugate() * Math::Vector(0.0, 0.0, 50.0), q);
    m_modelStage->camera()->step(sinceLast.toUsec() / 1e3);
    

    m_pipeline->render();
    
    Interface::Video::instance()->swapBuffers();
}

void ModelViewerContext::quitMenu(bool pressed) {
    if(!activated()) return;

    if(pressed) Context::ContextManager::instance()->popContext();
}

}  // namespace Kriti
