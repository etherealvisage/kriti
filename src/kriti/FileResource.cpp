#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

#include <boost/algorithm/string.hpp>

#include "FileResource.h"
#include "XMLResource.h"
#include "ResourceRegistry.h"

namespace Kriti {

FileResource::FileResource() : m_contentLoaded(false) {

}

FileResource::~FileResource() {

}

bool FileResource::loadFrom(std::string filename) {
    std::string prefix = ResourceRegistry::get<XMLResource>(
            "config"
        )->doc().first_element_by_path(
            "/kriti/general/data-path"
        ).text().as_string("data/");

    m_filename = prefix + filename;
    if(!boost::filesystem::exists(m_filename)) return false;

    return true;
}

const std::string &FileResource::fileContent() {
    if(!m_contentLoaded) loadFile();

    return m_content;
}

std::vector<std::string> FileResource::fileLines() {
    if(!m_contentLoaded) loadFile();

    std::vector<std::string> lines;

    boost::split(lines, m_content, boost::algorithm::is_any_of("\n\r"),
        boost::algorithm::token_compress_off);

    for(auto &line : lines) {
        line += "\n";
    }

    return lines;
}

void FileResource::loadFile() {
    std::ifstream f(m_filename.c_str());

    f.seekg(0, f.end);
    int length = f.tellg();
    f.seekg(0, f.beg);

    char *buffer = new char[length];
    f.read(buffer, length);
    m_content = std::string(buffer, length);
    delete[] buffer;

    m_contentLoaded = true;
}

}  // namespace Kriti
