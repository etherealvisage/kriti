#ifndef KRITI_GUI__FONT_H
#define KRITI_GUI__FONT_H

#include "Resource.h"

namespace Kriti {
namespace GUI {

class Font : public Resource {
private:
    
public:
    Font() {}

    virtual bool loadFrom(std::string identifier);
};

}  // namespace GUI
}  // namespace Kriti

#endif
