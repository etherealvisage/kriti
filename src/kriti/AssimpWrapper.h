#ifndef KRITI__ASSIMP_WRAPPER_H
#define KRITI__ASSIMP_WRAPPER_H

#include <boost/shared_ptr.hpp>

#include <assimp/LogStream.hpp>
#include <assimp/types.h>

#include "math/Vector.h"
#include "math/Matrix.h"

#include "Globals.h"
#include "MessageSystem.h"

namespace Kriti {

class AssimpWrapper { KRITI_GLOBAL(AssimpWrapper)
private:
    template<MessageSystem::MessageType type>
    class LogStream : public Assimp::LogStream {
    public:
        virtual ~LogStream() {}

        void write(const char *message) {
            MessageSystem::message("Assimp", type, message);
        }
    };
public:
    AssimpWrapper();
public:
    ~AssimpWrapper();

    static Math::Vector convertVector(const aiVector3D &vector);
    static Math::Vector convertColour(const aiColor3D &colour);
    static Math::Vector convertColour(const aiColor4D &colour);
    static aiColor3D convertColour(const Math::Vector &colour);

    static Math::Matrix convertMatrix(const aiMatrix4x4 &matrix);
};

}  // namespace Kriti

#endif
