#ifndef KRITI_GUI__TEXT_WRAPPER_H
#define KRITI_GUI__TEXT_WRAPPER_H

#include <vector>

namespace Kriti {
namespace GUI {

class TextWrapper {
public:
private:

public:
    std::vector<std::vector<Block>> wrap(const std::vector<Block> &blocks,
        double maxWidth);
};

}  // namespace GUI
}  // namespace Kriti

#endif
