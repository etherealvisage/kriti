#ifndef KRITI__ASSIMP_WRAPPER_H
#define KRITI__ASSIMP_WRAPPER_H

#include <boost/shared_ptr.hpp>

#include <assimp/LogStream.hpp>
#include <assimp/types.h>

#include "math/Vector.h"

#include "MessageSystem.h"

namespace Kriti {

class AssimpWrapper {
private:
    template<MessageSystem::MessageType type>
    class LogStream : public Assimp::LogStream {
    public:
        virtual ~LogStream() {}

        void write(const char *message) {
            MessageSystem::message(MessageSystem::Assimp, type, message);
        }
    };
private:
    static boost::shared_ptr<AssimpWrapper> s_singleton;
public:
    static boost::shared_ptr<AssimpWrapper> instance() {
        if(!s_singleton) {
            s_singleton =
                boost::shared_ptr<AssimpWrapper>(new AssimpWrapper());
        }

        return s_singleton;
    }

    static void destroy() {
        s_singleton.reset();
    }
private:
    AssimpWrapper();
public:
    ~AssimpWrapper();

    static Math::Vector convertVector(const aiVector3D &vector);
    static Math::Vector convertColour(const aiColor3D &colour);
    static Math::Vector convertColour(const aiColor4D &colour);
    static aiColor3D convertColour(const Math::Vector &colour);
};

}  // namespace Kriti

#endif
