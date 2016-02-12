#ifndef KRITI_GUI__TEXT_DISPLAY_H
#define KRITI_GUI__TEXT_DISPLAY_H

#include "Widget.h"
#include "Font.h"

namespace Kriti {
namespace GUI {

class TextDisplay : public Widget {
public:
    enum VerticalAlignment {
        Top,
        VCentre,
        Bottom 
    };
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Font::Instance> m_font;
    std::string m_text;
    Math::Vector m_colour;
    VerticalAlignment m_valign;
    Math::Vector m_lastScale;
    bool m_reflow;
    bool m_regen;
    std::vector<std::string> m_lines;
public:
    TextDisplay(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font::Instance> font,
        Math::Vector colour = Math::Vector(1.0,1.0,1.0),
        VerticalAlignment valign = Top);
    
    std::string text() const { return m_text; }
    void setText(std::string text)
        { m_text = text; m_regen = true; m_reflow = true; }

    virtual Math::Vector minSize();

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
    virtual void flush(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);

    void flowText(double overall_width);
};

}  // namespace GUI
}  // namespace Kriti

#endif
