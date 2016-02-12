#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include "TextDisplay.h"
#include "TextRenderer.h"

#include "../MessageSystem.h"

namespace Kriti {
namespace GUI {

TextDisplay::TextDisplay(Math::Vector minSize, Math::Vector stretch,
    boost::shared_ptr<Font::Instance> font, Math::Vector colour,
    VerticalAlignment valign) : Widget(stretch), m_minSize(minSize),
    m_font(font), m_colour(colour), m_valign(valign) {

    m_regen = false;
    m_reflow = false;
}

Math::Vector TextDisplay::minSize() {
    if(m_reflow) {
        flowText(m_minSize.x());
        Math::Vector spacing(0.0,0.02);
        m_minSize.setY(spacing.y() * m_lines.size());
    }
    return m_minSize;
}

void TextDisplay::fill(
    boost::shared_ptr<Render::RenderableContainer> container) {

    if(m_renderable) container->addTransparent(m_renderable);
}

void TextDisplay::flush(
    boost::shared_ptr<Render::RenderableContainer> container) {

    if(m_renderable) container->removeTransparent(m_renderable);
}

void TextDisplay::updated(
    boost::shared_ptr<OutlineRegistry> __attribute__((unused)) registry,
        Math::Vector clipStart, Math::Vector clipEnd) {

    Math::Vector outlineStart, outlineEnd;
    standardOutlineUpdate(nullptr, clipStart, clipEnd, outlineStart,
        outlineEnd);

    if(!m_renderable) m_renderable = boost::make_shared<Render::Renderable>();
    else if(m_regen || m_lastScale != scale()) {
        m_renderable->clearRenderSequences();
        m_regen = false;
        // XXX: text should have been flowed already by call to minSize().
        if(m_reflow) {
            flowText(size().x());
            m_reflow = false;
        }

        Math::Vector spacing(0,-0.02);
        Math::Vector offset;
        for(auto &line : m_lines) {
            auto rline = TextRenderer().renderString(m_font, line, m_colour,
                scale());

            auto seq = rline->renderSequence(0);
            Math::AffineTransformation at;
            at.translate(offset);
            seq->sequenceTransform() *= at.matrix();

            rline->renderSequence(0)->extraParams().setParam("gui_clip_start",
                clipStart);
            rline->renderSequence(0)->extraParams().setParam("gui_clip_end",
                clipEnd);

            m_renderable->addRenderSequence(rline->renderSequence(0));

            offset += spacing;
        }
    }

    m_lastScale = scale();

    Math::Vector offset;
    switch(m_valign) {
    case Top:
        m_renderable->location() = pos() + Math::Vector(0.0, size().y());
        break;
    case VCentre:
        Message3(GUI, Debug, "VCentre TextDisplay alignment NYI");
        m_renderable->location() = pos();
        break;
    case Bottom:
        Message3(GUI, Debug, "Bottom TextDisplay alignment NYI");
        m_renderable->location() = pos();
        break;
    }

}

void TextDisplay::flowText(double overall_width) {
    m_lines.clear();
    std::vector<std::string> paragraphs;
    boost::split(paragraphs, m_text, boost::algorithm::is_any_of("\n\r"),
        boost::algorithm::token_compress_off);

    for(auto &paragraph : paragraphs) {
        std::vector<std::string> words;
        boost::split(words, paragraph,
            boost::algorithm::is_any_of("\t "),
            boost::algorithm::token_compress_on);

        std::string line;
        double running_width = 0;
        for(auto word : words) {
            if(running_width != 0) word = " " + word;
            Math::Vector ul, lr;
            TextRenderer().sizeString(m_font, word, ul, lr);
            double width = lr.x() - ul.x();
            // can we fit it on the current line?
            if(running_width + width <= overall_width) {
                line += word;
                running_width += width;
                continue;
            }
            // remove the space
            word = word.substr(1);
            TextRenderer().sizeString(m_font, word, ul, lr);
            running_width = width;
            m_lines.push_back(line);
            line = word;
        }
        m_lines.push_back(line);
    }
}

}  // namespace GUI
}  // namespace Kriti
