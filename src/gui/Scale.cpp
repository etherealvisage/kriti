#include "Scale.h"

#include "interface/Video.h"

#include "config/Tree.h"

namespace Kriti {
namespace GUI {

double Scale::defaultWidth() {
    return Interface::Video::instance()->aspectRatio()
        / Interface::Video::instance()->width()
        * Config::Tree::instance()->getDouble("gui.scale", 100.0);
}

double Scale::defaultHeight() {
    return 2.0 / Interface::Video::instance()->height()
        * Config::Tree::instance()->getDouble("gui.scale", 100.0);
}

}  // namespace GUI
}  // namespace Kriti
