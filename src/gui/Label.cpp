#include "Label.h"
#include "TextRenderer.h"
#include "Scale.h"

#include "render/Stage.h"
#include "render/RenderableFactory.h"

#include "XMLResource.h"
#include "ResourceRegistry.h"

namespace Kriti {
namespace GUI {

Label::Label(Math::Vector stretch, boost::shared_ptr<Font> font,
    std::string text, HorizontalAlignment halign, VerticalAlignment valign)
    : Widget(stretch), m_font(font), m_text(text), m_halign(halign),
    m_valign(valign), m_regen(true) {

    m_textScale = ResourceRegistry::get<XMLResource>(
        "config")->doc().first_element_by_path(
        "/kriti/gui/text-scale").text().as_double(0.3);
}

Math::Vector Label::minSize() {
    Math::Vector ul, lr;
    TextRenderer().size(m_font, m_text, ul, lr);

    ul = ul * m_textScale;
    lr = lr * m_textScale;

    return lr-ul;
}

void Label::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->add(m_renderable);
}

void Label::updated(
    boost::shared_ptr<OutlineRegistry> __attribute__((unused)) registry) {

    if(!m_renderable) {
        m_renderable = TextRenderer().render(m_font, m_text, scale()*m_textScale);
    }
    else if(!(m_lastScale == scale()) || m_regen) {
        auto temp = TextRenderer().render(m_font, m_text, scale()*m_textScale);
        m_renderable->clearRenderSequences();
        m_renderable->addRenderSequence(temp->renderSequence(0));
        m_regen = false;
    }

    Math::Vector ul, lr;
    TextRenderer().size(m_font, m_text, ul, lr);
    ul = ul * m_textScale * scale();
    lr = lr * m_textScale * scale();

    double hspace = (size().x() - (lr.x() - ul.x()));
    double vspace = (size().y() - (lr.y() - ul.y()));

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
}

}  // namespace GUI
}  // namespace Kriti
