#ifndef KRITI_GUI__BUTTON_H
#define KRITI_GUI__BUTTON_H

#include "Widget.h"
#include "Label.h"
#include "Panel.h"

namespace Kriti {
namespace GUI {

class Button : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Panel> m_panel;
    boost::shared_ptr<Label> m_label;
public:
    Button(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font::Instance> font, std::string text);

    virtual Math::Vector minSize();

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
