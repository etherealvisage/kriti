#include "Scale.h"

#include "../interface/Video.h"

#include "../ResourceRegistry.h"
#include "../XMLResource.h"

namespace Kriti {
namespace GUI {

double Scale::defaultWidth() {
    return xscale() *
        ResourceRegistry::get<XMLResource>(
        "config")->doc().first_element_by_path(
        "/kriti/gui/scale").text().as_double(100.0);
}

double Scale::defaultHeight() {
    return yscale() *
        ResourceRegistry::get<XMLResource>(
        "config")->doc().first_element_by_path(
        "/kriti/gui/scale").text().as_double(100.0);
}

Math::Vector Scale::padding() {
    return Math::Vector(xtotal()/100.0, ytotal()/100.0);
}

Math::Vector Scale::perLayer() {
    return Math::Vector(0.0, 0.0, 0.1);
}

double Scale::xscale() {
    /*return (2*Interface::Video::instance()->aspectRatio())
        / Interface::Video::instance()->width();*/
    return 1.0 / Interface::Video::instance()->width();
}

double Scale::yscale() {
    /*return 2.0 / Interface::Video::instance()->height();*/
    return 1.0 / Interface::Video::instance()->height();
}

double Scale::xtotal() {
    return 2*Interface::Video::instance()->aspectRatio();
}

double Scale::ytotal() {
    return 2.0;
}

double Scale::fromPixelsX(int count) {
    return xscale() * count * xtotal();
}

double Scale::fromPixelsY(int count) {
    return yscale() * count * ytotal();
}

}  // namespace GUI
}  // namespace Kriti