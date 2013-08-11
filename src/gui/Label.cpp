#include "Label.h"
#include "TextRenderer.h"
#include "Scale.h"

#include "render/Stage.h"
#include "render/RenderableFactory.h"

#include "config/Tree.h"

namespace Kriti {
namespace GUI {

Label::Label(Math::Vector stretch, boost::shared_ptr<Render::Stage> stage,
    boost::shared_ptr<Font> font, std::string text,
    HorizontalAlignment halign, VerticalAlignment valign)
    : Widget(stretch, stage), m_font(font), m_text(text), m_halign(halign),
    m_valign(valign) {

    m_textScale = Config::Tree::instance()->getDouble("gui.text_scale", 0.3);
}

Math::Vector Label::minSize() {
    Math::Vector ul, lr;
    TextRenderer().size(m_font, m_text, ul, lr);

    ul = ul * m_textScale;
    lr = lr * m_textScale;

    return lr-ul;
}

void Label::updated(boost::shared_ptr<OutlineRegistry> registry) {
    // TODO: re-use old renderable . . . this is expensive.
    if(m_renderable) m_stage->removeRenderable(m_renderable);

    m_renderable = TextRenderer().render(m_font, m_text, scale()*m_textScale);

    Math::Vector ul, lr;
    TextRenderer().size(m_font, m_text, ul, lr);
    ul = ul * m_textScale;
    lr = lr * m_textScale;

    double hspace = size().x() - (lr.x() - ul.x());
    double vspace = size().y() - (lr.y() - ul.y());

    Math::Vector offset;
    switch(m_halign) {
    case Left:
        break;
    case HCentre:
        offset += Math::Vector(hspace/2.0);
        break;
    case Right:
        offset += Math::Vector(hspace);
        break;
    }

    switch(m_valign) {
    case Top:
        break;
    case VCentre:
        offset -= Math::Vector(0.0, vspace/2.0);
        break;
    case Bottom:
        offset -= Math::Vector(0.0, vspace);
        break;
    }

    m_renderable->location()
        = pos() + Math::Vector(0.0, size().y() - (lr.y() - ul.y())) + offset;

    m_stage->addRenderable(m_renderable);
}

}  // namespace GUI
}  // namespace Kriti
