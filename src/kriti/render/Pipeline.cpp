#include <boost/make_shared.hpp>

#include "Pipeline.h"

#include "../math/ViewGenerator.h"

#include "../interface/Video.h"

#include "../MessageSystem.h"
#include "../ResourceRegistry.h"
#include "../XMLResource.h"

namespace Kriti {
namespace Render {

bool Pipeline::loadFrom(std::string identifier) {
    std::string stageName = ResourceRegistry::get<XMLResource>(
            "data"
        )->doc().first_element_by_path(
            "/kriti/render/"
        ).find_child_by_attribute(
            "pipeline", "name", identifier.c_str()
        ).attribute("last").as_string("");

    if(stageName == "") return false;

    m_lastStage = ResourceRegistry::get<Stage>(stageName);

    if(!m_lastStage) return false;

    return true;
}

void Pipeline::render() {
    Uniforms u;
    u.setParam("u_time", static_cast<int>(TimeValue::current().toMsec()));
    u.setParam("u_msaaSamples", Interface::Video::instance()->aasamples());

    m_rendered.clear();
    render(u, m_lastStage);
}

void Pipeline::render(Uniforms &tp, boost::shared_ptr<Stage> stage) {
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
