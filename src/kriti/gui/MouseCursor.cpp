#include "MouseCursor.h"

#include "Scale.h"

#include "../render/RenderableFactory.h"

#include "../interface/Video.h"

namespace Kriti {
namespace GUI {

MouseCursor::MouseCursor() {
    Math::Vector hsize(Scale().fromPixelsX(32));
    Math::Vector vsize(0, -Scale().fromPixelsY(32));
    Math::Vector base;// = -hsize/2 - vsize/2;
    m_renderable = Render::RenderableFactory().fromQuad(base, base + vsize,
        base + vsize+hsize, base + hsize, "gui_cursor");
}

void MouseCursor::updateMouseCoordinates(double x, double y) {
    Math::Vector mpos(x, y);
    m_renderable->location() = Math::Vector(x, y, 8.0);
}

}  // namespace GUI
}  // namespace Kriti
