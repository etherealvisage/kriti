#ifndef KRITI_GUI__SCALE_H
#define KRITI_GUI__SCALE_H

#include "math/Vector.h"

namespace Kriti {
namespace GUI {

class Scale {
public:
    /// default width/height scale of GUI elements
    double defaultWidth();
    double defaultHeight();

    /// default padding around elements/between elements
    Math::Vector padding();
    /// z-spacing between elements layered on top of each other
    Math::Vector perLayer();

    /// what percentage of the screen is one horizontal pixel unit?
    double xscale();
    /// what percentage of the screen is one vertical pixel unit?
    double yscale();

    /// how many horizontal units for the viewport?
    double xtotal();
    /// how many vertical units for the viewport?
    double ytotal();

    /// how many horizontal units for count pixels?
    double fromPixelsX(int count);
    /// how many vertical units for count pixels?
    double fromPixelsY(int count);
};

}  // namespace GUI
}  // namespace Kriti

#endif
