#include <GL/glew.h>

#include "Pipeline.h"

#include "config/Tree.h"

#include "math/ViewGenerator.h"

#include "MessageSystem.h"


namespace Kriti {
namespace Render {

Pipeline::Pipeline() {
}

void Pipeline::render() {
    m_rendered.clear();
    render(m_lastStage);
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
