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
    static boost::shared_ptr<ResourceRegistry> s_singleton;
public:
    static boost::shared_ptr<ResourceRegistry> instance() {
        if(!s_singleton) {
            s_singleton
                = boost::shared_ptr<ResourceRegistry>(new ResourceRegistry());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    std::map<std::string, boost::shared_ptr<Resource>> m_resources;
private:
    ResourceRegistry();
public:
    ~ResourceRegistry();

    template<typename ResourceType>
    boost::shared_ptr<ResourceType> get(
        std::string identifier) {

        auto ir = m_resources.find(typeid(ResourceType).name() + identifier);

        boost::shared_ptr<Resource> result;
        if(ir == m_resources.end()) {
            result = boost::shared_ptr<ResourceType>(new ResourceType());

            if(!result->loadFrom(identifier)) {
                Message3(General, Warning,
                    "Could not locate resource with identifier \""
                    << identifier << "\"");
                result.reset();
            }
            m_resources[typeid(ResourceType).name() + identifier] = result;
        }
        else result = (*ir).second;

        return boost::dynamic_pointer_cast<ResourceType>(result);
    }
};

}  // namespace Kriti

#endif
