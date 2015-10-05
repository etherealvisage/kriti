#ifndef KRITI_GUI__BUTTON_H
#define KRITI_GUI__BUTTON_H

#include "Widget.h"
#include "Label.h"

#include "../state/Context.h"

namespace Kriti {
namespace GUI {

class Button : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Label> m_label;
    double m_activation;
    bool m_wasClicked;

    boost::weak_ptr<State::Context::Event> m_clickEvent;
public:
    Button(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font::Instance> font, std::string text);

    void setClickEvent(boost::weak_ptr<State::Context::Event> clickEvent)
        { m_clickEvent = clickEvent; }

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
