#include "MouseCursor.h"

#include "Scale.h"

#include "render/RenderableFactory.h"

#include "interface/Video.h"

namespace Kriti {
namespace GUI {

MouseCursor::MouseCursor() {
    Math::Vector hsize(Scale().fromPixelsX(32));
    Math::Vector vsize(0, -Scale().fromPixelsY(32));
    Math::Vector base;// = -hsize/2 - vsize/2;
    m_renderable = Render::RenderableFactory().fromQuad(base, base + vsize,
        base + vsize+hsize, base + hsize, "gui_cursor");
}

void MouseCursor::updateMouseCoordinates(int x, int y) {
    Math::Vector mpos(
        ((double)x / Interface::Video::instance()->width())
            *Scale().xtotal() - Scale().xtotal()/2,
        // invert mouse Y coordinates
        -((double)y / Interface::Video::instance()->height())
            *Scale().ytotal() + Scale().ytotal()/2);
    m_renderable->location() = mpos + Math::Vector(0.0, 0.0, 100.0);
}

}  // namespace GUI
}  // namespace Kriti
