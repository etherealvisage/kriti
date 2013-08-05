#include <GL/glew.h>

#include "Pipeline.h"

#include "MessageSystem.h"

#include "math/ViewGenerator.h"

namespace Kriti {
namespace Render {

void Pipeline::render() {
    m_rendered.clear();
    render(m_lastStage);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);

    //m_lastStage->framebuffer()->bindRead();

    //glBlitFramebuffer(0, 0, 1023, 767, 0, 0, 1023, 767,
        //GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void Pipeline::render(boost::shared_ptr<Stage> stage) {
    // check if it's already been rendered.
    if(m_rendered.find(stage) != m_rendered.end()) return;

    // render all previous
    for(int i = 0; i < stage->previousCount(); i ++) {
        render(stage->previous(i));
    }

    stage->render(stage == m_lastStage);

    m_rendered.insert(stage);
}

}  // namespace Render
}  // namespace Kriti
