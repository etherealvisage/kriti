#ifndef KRITI_RENDER__STAGE_H
#define KRITI_RENDER__STAGE_H

#include <vector>
#include <tuple>

#include "Renderable.h"
#include "SceneCamera.h"

#include "Framebuffer.h"

namespace Kriti {
namespace Render {

class TextureContext;

class Stage {
private:
    std::vector<boost::shared_ptr<Stage>> m_previous;
    std::vector<boost::shared_ptr<Renderable>> m_objects;
    SceneCamera m_camera;

    boost::shared_ptr<Framebuffer> m_framebuffer;
    boost::shared_ptr<TextureContext> m_textureContext;

    // what stage is it from, what attachment on that stage's framebuffer,
    // and what uniform to fill with the sampler2D.
    std::vector<std::tuple<boost::shared_ptr<Stage>, Framebuffer::Attachment,
        std::string>> m_attachments;

    int m_width, m_height;
    std::string m_name;
public:
    Stage(int outputs, int width, int height, std::string name);
    Stage(std::string name) : Stage(1, -1, -1, name) {}

    SceneCamera *camera() { return &m_camera; }

    void addPrevious(boost::shared_ptr<Stage> previous)
        { m_previous.push_back(previous); }

    boost::shared_ptr<Stage> previous(int which) const
        { return m_previous[which]; }
    int previousCount() const { return m_previous.size(); }

    void addMapping(int previousIndex, Framebuffer::Attachment attachment,
        std::string uniformName);

    boost::shared_ptr<Framebuffer> framebuffer() const
        { return m_framebuffer; }

    void addRenderable(boost::shared_ptr<Renderable> renderable);
    void removeRenderable(boost::shared_ptr<Renderable> renderable);

    void render(TechniqueParams &globalParams, bool isLast = false);
};

}  // namespace Render
}  // namespace Kriti

#endif
