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

GLuint g_vaoID, g_vboID;

MainMenuContext::MainMenuContext() {
    Interface::DeviceManager::instance()->keyboardRouter()->signal(
            Interface::KeyboardRouter::GUI_exit
        ).connect(
            boost::bind(&MainMenuContext::quitMenu, this, _1)
        );
    m_simpleModel = ResourceRegistry::instance()->get<Render::Model>("simple");
    m_pipeline = new Render::Pipeline();

    m_pipeline->camera()->setProjection(Math::ViewGenerator().perspective(
        Math::Constants::Pi/3.0, 4.0/3.0, 0.01, 100.0
    ));

    /*m_pipeline->camera()->setTarget(Math::Vector(0.0, 0.0, 10.0),
        Math::Quaternion());*/

    m_pipeline->camera()->step(0.0);

    m_simpleRenderable =
        Render::RenderableFactory().fromModel(m_simpleModel);

    m_simpleRenderable->location() = Math::Vector(0.0, 0.0, -10.0);
    m_pipeline->addRenderable(m_simpleRenderable);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GEQUAL);
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.03f, 0.03f, 0.03f, 1.0f);

    glGenVertexArrays(1, &g_vaoID);
    glBindVertexArray(g_vaoID);
    glGenBuffers(1, &g_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, g_vboID);

    const float vertexData[] = {
        0.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData,
        GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void MainMenuContext::run() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_simpleRenderable->orientation() = m_simpleRenderable->orientation()
        * Math::Quaternion(Math::Vector(0.0, 1.0, 0.0), 0.01);

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
