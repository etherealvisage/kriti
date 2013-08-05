#ifndef KRITI_RENDER__STAGE_H
#define KRITI_RENDER__STAGE_H

#include <vector>

#include "Renderable.h"
#include "SceneCamera.h"

#include "Framebuffer.h"

namespace Kriti {
namespace Render {

class Stage {
private:
    std::vector<boost::shared_ptr<Stage>> m_previous;
    std::vector<boost::shared_ptr<Renderable>> m_objects;
    SceneCamera m_camera;

    boost::shared_ptr<Framebuffer> m_framebuffer;
    boost::shared_ptr<Renderbuffer> m_colourOutput, m_depthOutput;
public:
    Stage();

    SceneCamera *camera() { return &m_camera; }

    void addPrevious(boost::shared_ptr<Stage> previous)
        { m_previous.push_back(previous); }

    boost::shared_ptr<Stage> previous(int which) const
        { return m_previous[which]; }
    int previousCount() const { return m_previous.size(); }

    boost::shared_ptr<Framebuffer> framebuffer() const { return m_framebuffer; }

    void addRenderable(boost::shared_ptr<Renderable> renderable);
    void removeRenderable(boost::shared_ptr<Renderable> renderable);

    void render(bool isLast = false);
};

}  // namespace Render
}  // namespace Kriti

#endif
