#ifndef KRITI_GUI__BUTTON_H
#define KRITI_GUI__BUTTON_H

#include "Widget.h"
#include "Label.h"

namespace Kriti {
namespace GUI {

class Button : public Widget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Label> m_label;
    double m_activation;
    bool m_wasClicked;
public:
    Button(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font> font, std::string text);

    virtual Math::Vector minSize();

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry);
};

}  // namespace GUI
}  // namespace Kriti

#endif
