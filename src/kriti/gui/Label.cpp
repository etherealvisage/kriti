#include "Label.h"
#include "TextRenderer.h"
#include "Scale.h"

#include "../render/Stage.h"
#include "../render/RenderableFactory.h"

#include "../XMLResource.h"
#include "../ResourceRegistry.h"

namespace Kriti {
namespace GUI {

Label::Label(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, std::string text,
    Math::Vector colour, HorizontalAlignment halign, VerticalAlignment valign)
    : Widget(stretch), m_minSize(minSize), m_font(font), m_text(text),
    m_colour(colour), m_halign(halign), m_valign(valign), m_regen(true) {

}

Math::Vector Label::minSize() {
    Math::Vector ul, lr;
    TextRenderer().sizeString(m_font, m_text, ul, lr);

    /*ul = ul * m_textScale;
    lr = lr * m_textScale;*/

    Math::Vector textMinSize = lr-ul;

    return Math::Vector(std::max(textMinSize.x(), m_minSize.x()),
        std::max(textMinSize.y(), m_minSize.y()));
}

void Label::fill(boost::shared_ptr<Render::RenderableContainer> container) {
    if(m_renderable) container->addTransparent(m_renderable);
}

void Label::updated(
    boost::shared_ptr<OutlineRegistry> __attribute__((unused)) registry,
        Math::Vector clipStart, Math::Vector clipEnd) {

    if(!m_renderable) {
        m_renderable = TextRenderer().renderString(m_font, m_text,
            Math::Vector(1.0, 1.0, 1.0), scale());
    }
    else if(!(m_lastScale == scale()) || m_regen) {
        auto temp = TextRenderer().renderString(m_font, m_text, scale());
        m_renderable->clearRenderSequences();
        m_renderable->addRenderSequence(temp->renderSequence(0));
        m_regen = false;
        m_lastScale = scale();
    }

    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_start",
        clipStart);
    m_renderable->renderSequence(0)->extraParams().setParam("gui_clip_end",
        clipEnd);

    Math::Vector ul, lr;
    TextRenderer().sizeString(m_font, m_text, ul, lr);
    ul = ul * scale();
    lr = lr * scale();

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
