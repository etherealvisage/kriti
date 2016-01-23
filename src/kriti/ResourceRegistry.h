#ifndef KRITI__RESOURCE_REGISTRY_H
#define KRITI__RESOURCE_REGISTRY_H

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

#include "Resource.h"
#include "MessageSystem.h"

namespace Kriti {

class ResourceRegistry {
private:
    static std::map<std::string, boost::shared_ptr<Resource>> s_resources;
private:
    ResourceRegistry() {}
    ~ResourceRegistry() {}
public:
    template<typename ResourceType>
    static boost::shared_ptr<ResourceType> get(
        std::string identifier) {

        auto ir = s_resources.find(typeid(ResourceType).name() + identifier);

        boost::shared_ptr<Resource> result;
        if(ir == s_resources.end()) {
            result = boost::shared_ptr<ResourceType>(new ResourceType());

            if(!result->loadFrom(identifier)) {
                Message3(General, Warning,
                    "Could not locate resource with identifier \""
                    << identifier << "\"");
                result.reset();
            }
            s_resources[typeid(ResourceType).name() + identifier] = result;
        }
        else result = (*ir).second;

        return boost::dynamic_pointer_cast<ResourceType>(result);
    }

    template<typename ResourceType>
    static void clear(std::string identifier) {
        auto r = s_resources.find(typeid(ResourceType).name() + identifier);

        if(r != s_resources.end()) s_resources.erase(r);
    }

    static void unload() {
        s_resources.clear();
    }
};

}  // namespace Kriti

#endif
