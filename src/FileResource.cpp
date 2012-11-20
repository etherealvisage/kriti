#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

#include "FileResource.h"
#include "config/Tree.h"

namespace Kriti {

FileResource::FileResource() {

}

FileResource::~FileResource() {

}

bool FileResource::loadFrom(std::string filename) {
    std::string prefix
        = Config::Tree::instance()->getString("kriti.data_path", "data/");
    filename = prefix + filename;
    if(!boost::filesystem::exists(filename)) return false;

    std::ifstream f(filename.c_str());

    m_content = "";
    std::string l;
    while(std::getline(f, l)) {
        m_content += l + "\n";
    }

    return true;
}

}  // namespace Kriti
