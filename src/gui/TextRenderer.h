#ifndef KRITI_GUI__TEXT_RENDERER_H
#define KRITI_GUI__TEXT_RENDERER_H

#include "Font.h"

#include "render/Renderable.h"

namespace Kriti {
namespace GUI {

class TextRenderer {
public:
    boost::shared_ptr<Render::Renderable> render(boost::shared_ptr<Font> font,
        std::string s, Math::Vector scale = Math::Vector(1.0, 1.0));

    void size(boost::shared_ptr<Font> font, std::string s, Math::Vector &ul,
        Math::Vector &lr);
};

}  // namespace GUI
}  // namespace Kriti

#endif
