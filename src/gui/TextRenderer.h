#ifndef KRITI_GUI__TEXT_RENDERER_H
#define KRITI_GUI__TEXT_RENDERER_H

#include "Font.h"

#include "render/Renderable.h"

namespace Kriti {
namespace GUI {

class TextRenderer {
public:
    boost::shared_ptr<Render::Renderable> render(boost::shared_ptr<Font> font,
        std::string s);
};

}  // namespace GUI
}  // namespace Kriti

#endif
