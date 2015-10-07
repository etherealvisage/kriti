#ifndef KRITI_GUI__TEXT_WRAPPER_H
#define KRITI_GUI__TEXT_WRAPPER_H

#include <vector>

#include "TextRenderer.h"

namespace Kriti {
namespace GUI {

class TextWrapper {
public:
    using Block = TextRenderer::Block;
private:

public:
    std::vector<std::vector<Block>> wrap(const std::vector<Block> &blocks,
        double maxWidth);
};

}  // namespace GUI
}  // namespace Kriti

#endif
