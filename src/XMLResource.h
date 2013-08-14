#ifndef KRITI__XMLRESOURCE_H
#define KRITI__XMLRESOURCE_H

#include <pugixml.hpp>

#include "Resource.h"

namespace Kriti {

class XMLResource : public Resource {
private:
    pugi::xml_document m_doc;
public:
    virtual bool loadFrom(std::string identifier);

    const pugi::xml_document &doc() const { return m_doc; }
};

}  // namespace Kriti

#endif
