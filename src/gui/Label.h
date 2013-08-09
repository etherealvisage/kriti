#ifndef KRITI_GUI__LABEL_H
#define KRITI_GUI__LABEL_H

#include <string>

#include "Widget.h"

namespace Kriti {
namespace GUI {

class Font;

class Label : public Widget {
private:
    boost::shared_ptr<Font> m_font;
    std::string m_text;
public:
    Label(Math::Vector stretch, boost::shared_ptr<Render::Stage> stage,
        boost::shared_ptr<Font> font, std::string text)
        : Widget(stretch, stage), m_font(font), m_text(text) {}

    virtual Math::Vector minSize();
protected:
    virtual void updated();
};

}  // namespace GUI
}  // namespace Kriti

#endif
