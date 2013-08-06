#ifndef KRITI_GUI__WIDGET_H
#define KRITI_GUI__WIDGET_H

#include "LayoutItem.h"

namespace Kriti {
namespace GUI {

class Widget : public LayoutItem {
private:
    Math::Vector m_minSize;
public:
    Widget();
};

}  // namespace GUI
}  // namespace Kriti

#endif
