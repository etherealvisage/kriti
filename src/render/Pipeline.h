#ifndef KRITI_RENDER__PIPELINE_H
#define KRITI_RENDER__PIPELINE_H

#include <set>

#include "Renderable.h"
#include "SceneCamera.h"
#include "Timer.h"

#include "Stage.h"

namespace Kriti {
namespace Render {

class Pipeline {
private:
    boost::shared_ptr<Stage> m_lastStage;

    std::set<boost::shared_ptr<Stage>> m_rendered;
public:
    Pipeline();

    void setLastStage(boost::shared_ptr<Stage> lastStage)
        { m_lastStage = lastStage; }

    void render();
private:
    void render(boost::shared_ptr<Stage> stage);
};

}  // namespace Render
}  // namespace Kriti

#endif
