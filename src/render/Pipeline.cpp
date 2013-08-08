#include <GL/glew.h>

#include "Pipeline.h"

#include "config/Tree.h"

#include "math/ViewGenerator.h"

#include "MessageSystem.h"


namespace Kriti {
namespace Render {

Pipeline::Pipeline() {
    m_profile = Config::Tree::instance()->getBool("video.profile", false);
}

void Pipeline::render() {
    if(m_profile) m_timer.begin();
    m_rendered.clear();
    render(m_lastStage);
    if(m_profile) m_timer.end();
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
