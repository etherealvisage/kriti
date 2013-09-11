#ifndef KRITI_RENDER__STAGE_H
#define KRITI_RENDER__STAGE_H

#include <vector>
#include <list>
#include <tuple>

#include "Renderable.h"
#include "SceneCamera.h"
#include "RenderableContainer.h"

#include "Framebuffer.h"

#include "Resource.h"

namespace Kriti {
namespace Render {

class TextureContext;

class Stage : public Resource {
private:
    std::vector<boost::shared_ptr<Stage>> m_previous;
    boost::shared_ptr<RenderableContainer> m_renderables;
    SceneCamera m_camera;

    boost::shared_ptr<Framebuffer> m_framebuffer;

    // what stage is it from, what attachment on that stage's framebuffer,
    // and what uniform to fill with the sampler2D.
    std::vector<std::tuple<boost::shared_ptr<Stage>, Framebuffer::Attachment,
        std::string>> m_attachments;

    int m_width, m_height;
    std::string m_name;

public:
    Stage();
    Stage(int outputs, int width, int height, std::string name);
    Stage(std::string name) : Stage(1, -1, -1, name) {}

    virtual bool loadFrom(std::string identifier);

    SceneCamera *camera() { return &m_camera; }

    void addPrevious(boost::shared_ptr<Stage> previous)
        { m_previous.push_back(previous); }

    boost::shared_ptr<Stage> previous(int which) const
        { return m_previous[which]; }
    int previousCount() const { return m_previous.size(); }

    boost::shared_ptr<RenderableContainer> renderables() const
        { return m_renderables; }

    void addMapping(int previousIndex, Framebuffer::Attachment attachment,
        std::string uniformName);

    boost::shared_ptr<Framebuffer> framebuffer() const
        { return m_framebuffer; }

    std::string name() const { return m_name; }

    void render(Uniforms &globalParams,
        boost::shared_ptr<TextureContext> textureContext, bool isLast = false);
private:
    void initialize(int outputs, int width, int height);

    void renderRenderable(Uniforms &globalParams,
        boost::shared_ptr<TextureContext> textureContext,
        boost::shared_ptr<Renderable> renderable);
};

}  // namespace Render
}  // namespace Kriti

#endif
