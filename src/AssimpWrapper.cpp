#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>

#include "AssimpWrapper.h"

namespace Kriti {

boost::shared_ptr<AssimpWrapper> AssimpWrapper::s_singleton;

AssimpWrapper::AssimpWrapper() {
    Assimp::Importer importer;

    Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);

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

}  // namespace Kriti
