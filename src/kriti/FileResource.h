#ifndef KRITI__FILE_RESOURCE_H
#define KRITI__FILE_RESOURCE_H

#include <vector>

#include "Resource.h"

namespace Kriti {

class FileResource : public Resource {
private:
    std::string m_filename;
    bool m_contentLoaded;
    std::string m_content;
public:
    FileResource();
    ~FileResource();

    virtual bool loadFrom(std::string filename);

    std::string filename() const { return m_filename; }
    std::string fileContent();
    std::vector<std::string> fileLines();
private:
    void loadFile();
};

}  // namespace Kriti

#endif
