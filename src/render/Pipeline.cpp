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
    TechniqueParams tp;
    tp.setParam("time", (int)TimeValue::current().toMsec());

    m_rendered.clear();
    render(tp, m_lastStage);
}

void Pipeline::render(TechniqueParams &tp, boost::shared_ptr<Stage> stage) {
    // check if it's already been rendered.
    if(m_rendered.find(stage) != m_rendered.end()) return;

    // render all previous
    for(int i = 0; i < stage->previousCount(); i ++) {
        render(tp, stage->previous(i));
    }

    stage->render(tp, stage == m_lastStage);

    m_rendered.insert(stage);
}

}  // namespace Render
}  // namespace Kriti
