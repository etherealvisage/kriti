#ifndef KRITI_GUI__MOUSE_CURSOR_H
#define KRITI_GUI__MOUSE_CURSOR_H

#include "../render/Renderable.h"

namespace Kriti {
namespace GUI {

class MouseCursor {
private:
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    MouseCursor();

    void updateMouseCoordinates(double x, double y);

    boost::shared_ptr<Render::Renderable> renderable() const
        { return m_renderable; }
};

}  // namespace GUI
}  // namespace Kriti

#endif
