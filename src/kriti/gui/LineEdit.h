#ifndef KRITI_GUI__LINE_EDIT_H
#define KRITI_GUI__LINE_EDIT_H

#include "Widget.h"
#include "Label.h"
#include "Panel.h"
#include "KeyboardFocusTarget.h"

#include "../state/Context.h"

namespace Kriti {
namespace GUI {

class LineEdit : public Widget, public KeyboardFocusTarget {
private:
    Math::Vector m_minSize;
    boost::shared_ptr<Panel> m_panel;
    boost::shared_ptr<Label> m_label;
    bool m_focused;
public:
    LineEdit(Math::Vector minSize, Math::Vector stretch,
        boost::shared_ptr<Font::Instance> font, std::string text = "");
    ~LineEdit();

    virtual Math::Vector minSize();

    virtual bool wantsFocus() { return true; }
    virtual bool wantsText() { return true; }
    virtual void lostFocus();
    virtual void gainedFocus();

    virtual void keyPressed(SDL_Keycode key);
    virtual void keyReleased(SDL_Keycode key);
    virtual void textEntered(std::string text);

    void requestFocus();
    /* Convenience function for when this is used as a KeyboardFocusTarget */
    boost::shared_ptr<LineEdit> targetPointer();

    std::string text() const;
    void setText(std::string text);

    virtual void fill(
        boost::shared_ptr<Render::RenderableContainer> container);
    virtual void flush(
        boost::shared_ptr<Render::RenderableContainer> container);
protected:
    virtual void updated(boost::shared_ptr<OutlineRegistry> registry,
        Math::Vector clipStart, Math::Vector clipEnd);
private:
};

}  // namespace GUI
}  // namespace Kriti

#endif
