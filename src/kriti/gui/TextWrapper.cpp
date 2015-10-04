#include "TextWrapper.h"

namespace Kriti {
namespace GUI {

std::vector<std::vector<TextWrapper::Block>> TextWrapper::wrap(
    const std::vector<TextWrapper::Block> &blocks, double maxWidth) {

    std::vector<std::vector<TextWrapper::Block>> lines;
    if(blocks.size() == 0) return lines;

    lines.push_back(std::vector<TextWrapper::Block>());

    double w = 0;
    for(auto &block : blocks) {
        double bw = block.width();
        if(w + bw > maxWidth)
            lines.push_back(std::vector<TextWrapper::Block>()), w = 0;
        lines.back().push_back(block);

        w += bw;
    }

    return lines;
}


}  // namespace GUI
}  // namespace Kriti
