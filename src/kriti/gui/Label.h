#ifndef KRITI_GUI__LABEL_H
#define KRITI_GUI__LABEL_H

#include <string>

#include "Widget.h"
#include "Font.h"

namespace Kriti {
namespace GUI {

class Label : public Widget {
public:
    enum HorizontalAlignment {
        Left,
        HCentre,
        Right
    };
    enum VerticalAlignment {
        Top,
        VCentre,
        Bottom 
    };
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Font::Instance> m_font;
    std::string m_text;
    HorizontalAlignment m_halign;
    VerticalAlignment m_valign;
    bool m_regen;
    Math::Vector m_lastScale;
public:
    Label(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font::Instance> font, std::string text,
        HorizontalAlignment halign = HCentre,
        VerticalAlignment valign = VCentre);

    std::string text() const { return m_text; }
    void setText(std::string text) { m_text = text; m_regen = true; }

    virtual Math::Vector minSize();

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);
};

}  // namespace GUI
}  // namespace Kriti

#endif
