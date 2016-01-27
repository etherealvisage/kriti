#include "Scale.h"

#include "../interface/Video.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"
#include "../Globals.h"

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
    return xtotal() / (Global<Interface::Video>()->width() / DPI);
}

double Scale::yscale() {
    return ytotal() / (Global<Interface::Video>()->height() / DPI);
}

double Scale::xtotal() {
    return Global<Interface::Video>()->aspectRatio();
}

double Scale::ytotal() {
    return 1.0;
}

double Scale::fromPixelsX(int count) {
    return (count * xtotal()) / Global<Interface::Video>()->width();
}

double Scale::fromPixelsY(int count) {
    return (count * ytotal()) / Global<Interface::Video>()->height();
}

double Scale::xDPI() {
    return DPI;
}

double Scale::yDPI() {
    return DPI;
}

}  // namespace GUI
}  // namespace Kriti
