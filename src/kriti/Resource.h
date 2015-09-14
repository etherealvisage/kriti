#ifndef KRITI__RESOURCE_H
#define KRITI__RESOURCE_H

#include <string>

namespace Kriti {

class Resource {
public:
    virtual ~Resource() {}

    virtual bool loadFrom(std::string identifier) = 0;
};

}  // namespace Kriti

#endif
