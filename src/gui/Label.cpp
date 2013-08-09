#include "Label.h"
#include "TextRenderer.h"

namespace Kriti {
namespace GUI {

Math::Vector Label::minSize() {
    Math::Vector ul, lr;
    TextRenderer().size(m_font, m_text, ul, lr);

    return lr-ul;
}

void Label::updated() {
    //m_renderable = 
}

}  // namespace GUI
}  // namespace Kriti
