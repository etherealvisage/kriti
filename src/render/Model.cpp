#include <sstream>

#include "Model.h"

#include "FileResource.h"
#include "ResourceRegistry.h"

namespace Kriti {
namespace Render {

bool Model::loadFrom(std::string identifier) {
    boost::shared_ptr<FileResource> file
        = ResourceRegistry::instance()->get<FileResource>("models/"
            + identifier + ".obj");
    if(!file) return false;

    Message3(Render, Log, "Loading model \"" << identifier << "\"");

    std::istringstream fileStream(file->fileContent());

    int sequenceStart = 0;
    std::string techniqueName;
    std::string line;
    while(std::getline(fileStream, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;
        // comment?
        if(line[0] == '#') continue;
        // vertex specification?
        else if(type == "v") {
            double x, y, z;
            ss >> x >> y >> z;
            m_objVertices.push_back(Math::Vector(x, y, z));
        }
        // normal specification?
        else if(type == "vn") {
            double x, y, z;
            ss >> x >> y >> z;
            m_objNormals.push_back(Math::Vector(x, y, z));
        }
        // normal specification?
        else if(type == "vt") {
            double x, y, z;
            ss >> x >> y >> z;
            m_objNormals.push_back(Math::Vector(x, y, z));
        }
        // face specification?
        else if(type == "f") {
            int vi, ti, ni;
            char dummy;
            for(int i = 0; i < 3; i ++) {
                ss >> vi;
                if(ss.peek() != '/') {
                    Message3(Render, Warning, "Malformed .OBJ file.");
                    return false;
                }
                ss >> dummy;

                if(ss.peek() != '/') ss >> ti;
                else ti = 0, ss >> dummy;
                if(ss.peek() != '/') ss >> ni;
                else ni = 0, ss >> dummy;
                addFaceEntry(vi-1, ti-1, ni-1);
            }
        }
        // new model sequence start?
        else if(type == "usemtl") {
            // avoid adding empty sequences.
            if(sequenceStart != static_cast<int>(m_indices.size())) {
                m_sequences.push_back(ModelSequence(techniqueName,
                    sequenceStart, m_indices.size()-1));
            }
            sequenceStart = m_indices.size();
            ss >> techniqueName;
        }
        else {
            Message3(Render, Debug, "Unknown command \"" << type
                << "\" in .OBJ model");
        }
    }

    // finish off last sequence if necessary.
    if(sequenceStart != static_cast<int>(m_indices.size())) {
        m_sequences.push_back(ModelSequence(techniqueName,
            sequenceStart, m_indices.size()-1));
    }

    Message3(Render, Debug, "Loaded OBJ model with " << m_indices.size()
        << " indices.");

    // clear temporary vectors.
    std::vector<Math::Vector>().swap(m_objVertices);
    std::vector<Math::Vector>().swap(m_objNormals);
    std::vector<Math::Vector>().swap(m_objTexCoords);
    std::map<std::tuple<int, int, int>, unsigned int>().swap(m_objIndices);

    return true;
}

void Model::addFaceEntry(int vi, int ti, int ni) {
    std::tuple<int, int, int> t(vi, ti, ni);

    auto fi = m_objIndices.find(t);
    // have we seen this combination before?
    if(fi != m_objIndices.end()) {
        m_indices.push_back(fi->second);
        return;
    }

    // add it.
    m_vertices.push_back(m_objVertices[vi]);
    if(ni != -1)
        m_normals.push_back(m_objNormals[ni]);
    else
        m_normals.push_back(Math::Vector());

    if(ti != -1)
        m_texCoords.push_back(m_objTexCoords[ti]);
    else
        m_texCoords.push_back(Math::Vector());
    m_objIndices[t] = m_vertices.size()-1;
    m_indices.push_back(m_vertices.size()-1);
}

}  // namespace Render
}  // namespace Kriti
