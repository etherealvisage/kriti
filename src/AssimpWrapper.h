#ifndef KRITI__ASSIMP_WRAPPER_H
#define KRITI__ASSIMP_WRAPPER_H

#include <boost/shared_ptr.hpp>

#include "MessageSystem.h"

#include <assimp/LogStream.hpp>

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

    
};

}  // namespace Kriti

#endif
