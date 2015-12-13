#include "Texture.h"

#include "../render/RenderableFactory.h"

namespace Kriti {
namespace GUI {

void Texture::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->addTransparent(m_renderable);
}

void Texture::flush(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->removeTransparent(m_renderable);
}

void Texture::updated(
    boost::shared_ptr<OutlineRegistry> __attribute__((unused)) registry,
        Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Vector xsize(size().x());
    Math::Vector ysize(0, size().x());
    // TODO: check these windings
    auto trender = Render::RenderableFactory().fromQuad(
        pos(), pos() + xsize, pos() + size(), pos() + ysize, "gui_textured");

    if(!m_renderable) {
        m_renderable = trender;
    }
    else {
        m_renderable->clearRenderSequences();
        m_renderable->addRenderSequence(trender->renderSequence(0));
    }

    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_start",
        clipStart);
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_end",
        clipEnd);

    m_renderable->location() = pos();
}

}  // namespace GUI
}  // namespace Kriti
