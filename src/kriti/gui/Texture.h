#ifndef KRITI_GUI__TEXTURE_H
#define KRITI_GUI__TEXTURE_H

#include "Widget.h"

namespace Kriti {

namespace Render {
class Texture;
class Renderable;
class RenderableContainer;
}  // namespace Render

namespace GUI {

class Texture : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Render::Texture> m_texture;

    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    Texture(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Render::Texture> texture) : Widget(stretch),
        m_minSize(minSize), m_texture(texture) {}

    virtual Math::Vector minSize() { return m_minSize; }

    void setTexture(boost::shared_ptr<Render::Texture> texture)
        { m_texture = texture; }

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
    virtual void flush(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);
};

}  // namespace GUI
}  // namespace Kriti

#endif
