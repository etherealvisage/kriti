#ifndef KRITI_GUI__FONT_H
#define KRITI_GUI__FONT_H

#include <map>

#include "../Resource.h"

namespace Kriti {
namespace GUI {

class Font : public Resource {
public:
    struct CharSpec {
        double x, y, w, h, xoff, yoff, xadv;
    };
private:
    std::string m_materialName;
    std::map<int, CharSpec> m_chars;
public:
    Font() {}

    std::string materialName() const { return m_materialName; }

    virtual bool loadFrom(std::string identifier);

    bool getCharSpec(int c, CharSpec &cs) const;
};

}  // namespace GUI
}  // namespace Kriti

#endif
