#include "XMLResource.h"

#include "FileResource.h"
#include "ResourceRegistry.h"

#include "MessageSystem.h"

#ifndef KRITI_CONFIG_PATH
    #error "KRITI_CONFIG_PATH must be defined"
#endif

namespace Kriti {

bool XMLResource::loadFrom(std::string identifier) {
    if(identifier == "config") {
        auto result = m_doc.load_file(KRITI_CONFIG_PATH);
        if(result) return true;

        Message3(General, Error, "Could not load XML resource " << identifier
            << ": " << result.description());

        return false;
    }

    // otherwise load from FileResource
    auto file = ResourceRegistry::get<FileResource>(identifier + ".xml");

    auto result = m_doc.load_buffer(file->fileContent().c_str(),
        file->fileContent().length());

    if(result) return true;

    Message3(General, Error, "Could not load XML resource " << identifier
        << ": " << result.description());

    return false;
}

}  // namespace Kriti
