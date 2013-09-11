#ifndef KRITI_RENDER__PIPELINE_H
#define KRITI_RENDER__PIPELINE_H

#include <set>

#include "Renderable.h"
#include "SceneCamera.h"
#include "Timer.h"

#include "Stage.h"

#include "Resource.h"

namespace Kriti {
namespace Render {

class Pipeline : public Resource {
private:
    std::string m_name;

    boost::shared_ptr<Stage> m_lastStage;

    std::set<boost::shared_ptr<Stage>> m_rendered;
public:
    virtual bool loadFrom(std::string identifier);

    void setLastStage(boost::shared_ptr<Stage> lastStage)
        { m_lastStage = lastStage; }

    void render(boost::shared_ptr<TextureContext> textureContext);
private:
    void render(Uniforms &tp, boost::shared_ptr<TextureContext> textureContext,
        boost::shared_ptr<Stage> stage);
};

}  // namespace Render
}  // namespace Kriti

#endif
