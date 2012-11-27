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

    Math::Matrix m = m_pipeline->camera()->matrix();

    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            std::cout << m(i, j) << " ";
        }
        std::cout << std::endl;
    }
    /*Math::Point p(0.0, 0.0, -10.0);
    p = m * p;
    Message("p transformed: " << p.x() << "," << p.y() << "," << p.z());*/

    m_pipeline->addRenderable(
        Render::RenderableFactory().fromModel(m_simpleModel));

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
    m_pipeline->render();

    glBindVertexArray(g_vaoID);
    auto shader = ResourceRegistry::instance()->get<Render::Technique>(
        "simple");

    shader->activate();
    shader->setUniform("camera", m_pipeline->camera()->matrix());
    Math::AffineTransformation at;
    at.translate(Math::Vector(0.2, 0.0, -20.0));
    shader->setUniform("model", at.matrix());

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    GLint err = glGetError();
    while(err != GL_NO_ERROR) {
        Message("GL error: " << gluErrorString(err));
        err = glGetError();
    }
    
    SDL_GL_SwapBuffers();
    SDL_Delay(30);
}

void MainMenuContext::quitMenu(bool) {
    if(!activated()) return;

    Context::ContextManager::instance()->popContext();
}

}  // namespace Game
}  // namespace Kriti
