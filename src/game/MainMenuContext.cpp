#include <GL/glew.h>

#include "MainMenuContext.h"

#include "SDL.h"

#include "ResourceRegistry.h"

#include "context/ContextManager.h"
#include "interface/DeviceManager.h"
#include "render/Model.h"
#include "render/RenderableFactory.h"
#include "math/ViewGenerator.h"
#include "math/Constants.h"
#include "math/AffineTransformation.h"

namespace Kriti {
namespace Game {

MainMenuContext::MainMenuContext() {
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::GUI_exit
        ).connect(
            boost::bind(&MainMenuContext::quitMenu, this, _1)
        );
    m_simpleModel = ResourceRegistry::instance()->get<Render::Model>("simple");
    m_pipeline = new Render::Pipeline();

    m_pipeline->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, 4.0/3.0, 0.01, 1000.0
    ));

    m_pipeline->camera()->setTarget(Math::Vector(0.0, 0.0, -100.0),
        Math::Quaternion());

    m_pipeline->camera()->step(0.0);

    m_simpleRenderable =
        Render::RenderableFactory().fromModel(m_simpleModel);

    m_simpleRenderable->location() = Math::Vector(0.0, 0.0, -10.0);
    m_pipeline->addRenderable(m_simpleRenderable);

    for(int i = 0; i < 100; i ++) {
        auto rp = Render::RenderableFactory().fromModel(m_simpleModel);
        rp->location() = Math::Vector(
            (rand()%1000)/5.0 + 10.0,
            (rand()%1000)/5.0 - 10.0,
            (rand()%1000)/5.0 - 10.0);

        rp->orientation() = Math::Quaternion(
            Math::Vector(0.1 + (rand()%1000)/1000.0,
                0.1 + (rand()%1000)/1000.0,
                0.1 + (rand()%1000)/1000.0).normalized(),
            (rand()%1000)/150.0
        );

        m_objects.push_back(rp);
        m_speeds.push_back(Math::Vector());
        m_pipeline->addRenderable(rp);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
}

void MainMenuContext::run() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*m_simpleRenderable->orientation() = m_simpleRenderable->orientation()
        * Math::Quaternion(Math::Vector(0.0, 1.0, 0.0), 0.01);*/

    static int steps = 0;
    m_pipeline->camera()->setTarget(Math::Vector(0.0, 0.0, -100.0 + 0*sin(steps/90.0)),
        Math::Quaternion(Math::Vector(0.0f, 1.0f, 0.0f), -Math::Constants::Pi));
    steps ++;
    m_pipeline->camera()->step(0.0);

    for(int i = 0; i < m_objects.size(); i ++) {
        for(int j = 0; j < m_objects.size(); j ++) {
            if(i == j) continue;

            auto v = m_objects[j]->location() - m_objects[i]->location();

            m_speeds[j] = m_speeds[j] - (v.normalized())/10000;
        }
    }

    for(int i = 0; i < m_objects.size(); i ++) {
        m_objects[i]->location() = m_objects[i]->location() + m_speeds[i];
    }

    m_pipeline->render();

    GLint err = glGetError();
    while(err != GL_NO_ERROR) {
        Message("GL error: " << gluErrorString(err));
        err = glGetError();
    }
    
    SDL_GL_SwapBuffers();
    //SDL_Delay(30);
}

void MainMenuContext::quitMenu(bool) {
    if(!activated()) return;

    Context::ContextManager::instance()->popContext();
}

}  // namespace Game
}  // namespace Kriti
