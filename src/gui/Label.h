#ifndef KRITI_GUI__LABEL_H
#define KRITI_GUI__LABEL_H

#include <string>

#include "Widget.h"

namespace Kriti {
namespace GUI {

class Font;

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
    boost::shared_ptr<Font> m_font;
    std::string m_text;
    HorizontalAlignment m_halign;
    VerticalAlignment m_valign;
    double m_textScale;
public:
    Label(Math::Vector stretch, boost::shared_ptr<Render::Stage> stage,
        boost::shared_ptr<Font> font, std::string text,
        HorizontalAlignment halign = HCentre,
        VerticalAlignment valign = VCentre);

    std::string text() const { return m_text; }
    void setText(std::string text) { m_text = text; }

    virtual Math::Vector minSize();
protected:
    virtual void updated();
};

}  // namespace GUI
}  // namespace Kriti

#endif
