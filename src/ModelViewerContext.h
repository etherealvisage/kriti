#ifndef KRITI__MODEL_VIEWER_CONTEXT_H
#define KRITI__MODEL_VIEWER_CONTEXT_H

#include "context/AbstractContext.h"

#include "render/Pipeline.h"

#include "TimeValue.h"

namespace Kriti {

class ModelViewerContext : public Context::AbstractContext {
private:
    boost::shared_ptr<Render::Pipeline> m_pipeline;
    boost::shared_ptr<Render::Stage> m_modelStage;

    TimeValue m_lastTime;
public:
    ModelViewerContext();

    virtual std::string contextName() { return "ModelViewerContext"; }
    
    virtual void run();
private:
    virtual void activateHook() { m_lastTime = TimeValue::current(); }
    virtual void deactivateHook() {}
private:
    void quitMenu(bool pressed);
};

}  // namespace Kriti

#endif
