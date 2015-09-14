#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>

#include "AssimpWrapper.h"

namespace Kriti {

boost::shared_ptr<AssimpWrapper> AssimpWrapper::s_singleton;

AssimpWrapper::AssimpWrapper() {
    Assimp::Importer importer;

    Assimp::DefaultLogger::create("", Assimp::Logger::NORMAL);

    Assimp::DefaultLogger::get()->attachStream(
        new LogStream<MessageSystem::Debug>(), Assimp::Logger::Debugging);
    Assimp::DefaultLogger::get()->attachStream(
        new LogStream<MessageSystem::Log>(), Assimp::Logger::Info);
    Assimp::DefaultLogger::get()->attachStream(
        new LogStream<MessageSystem::Warning>(), Assimp::Logger::Warn);
    Assimp::DefaultLogger::get()->attachStream(
        new LogStream<MessageSystem::Error>(), Assimp::Logger::Err);
}

AssimpWrapper::~AssimpWrapper() {
    Assimp::DefaultLogger::kill();
}

Math::Vector AssimpWrapper::convertVector(const aiVector3D &vector) {
    return Math::Vector(vector.x, vector.y, vector.z);
}

Math::Vector AssimpWrapper::convertColour(const aiColor3D &colour) {
    return Math::Vector(colour.r, colour.g, colour.b);
}

Math::Vector AssimpWrapper::convertColour(const aiColor4D &colour) {
    // TODO: handle alpha channel
    return Math::Vector(colour.r, colour.g, colour.b);
}

aiColor3D AssimpWrapper::convertColour(const Math::Vector &colour) {
    return aiColor3D(colour.x(), colour.y(), colour.z());
}

Math::Matrix AssimpWrapper::convertMatrix(const aiMatrix4x4 &matrix) {
    Math::Matrix result;

    for(int i = 0; i < 4; i ++) {
        for(int j = 0; j < 4; j ++) {
            result(i, j) = matrix[i][j];
        }
    }

    return result;
}

}  // namespace Kriti
