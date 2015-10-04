#include "Scale.h"

#include "../interface/Video.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"

#define DPI 96

namespace Kriti {
namespace GUI {

Math::Vector Scale::padding() {
    return Math::Vector(xtotal()/100.0, ytotal()/100.0);
}

Math::Vector Scale::perLayer() {
    return Math::Vector(0.0, 0.0, 0.1);
}

double Scale::xscale() {
    return xtotal() / (Interface::Video::instance()->width() / DPI);
}

double Scale::yscale() {
    return ytotal() / (Interface::Video::instance()->height() / DPI);
}

double Scale::xtotal() {
    return Interface::Video::instance()->aspectRatio();
}

double Scale::ytotal() {
    return 1.0;
}

double Scale::fromPixelsX(int count) {
    return (count * xtotal()) / Interface::Video::instance()->width();
}

double Scale::fromPixelsY(int count) {
    return (count * ytotal()) / Interface::Video::instance()->height();
}

double Scale::xDPI() {
    return DPI;
}

double Scale::yDPI() {
    return DPI;
}

}  // namespace GUI
}  // namespace Kriti
