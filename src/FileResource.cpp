#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

#include "FileResource.h"
#include "config/Tree.h"

namespace Kriti {

FileResource::FileResource() : m_contentLoaded(false) {

}

FileResource::~FileResource() {

}

bool FileResource::loadFrom(std::string filename) {
    std::string prefix
        = Config::Tree::instance()->getString("kriti.data_path", "data/");
    m_filename = prefix + filename;
    if(!boost::filesystem::exists(m_filename)) return false;

    return true;
}

std::string FileResource::fileContent() {
    if(!m_contentLoaded) loadFile();

    return m_content;
}

void FileResource::loadFile() {
    std::ifstream f(m_filename.c_str());

    m_content = "";
    std::string l;
    while(std::getline(f, l)) {
        m_content += l + "\n";
    }

    m_contentLoaded = true;
}

}  // namespace Kriti
