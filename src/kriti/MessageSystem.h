#ifndef KRITI__MESSAGE_SYSTEM_H
#define KRITI__MESSAGE_SYSTEM_H

#include <iosfwd>

#include "StreamAsString.h"

#define MS_Types \
    MS_Type(Debug), \
    MS_Type(Log), \
    MS_Type(Warning), \
    MS_Type(Error), \
    MS_Type(Fatal)

namespace Kriti {

class MessageSystem {
public:
    enum MessageType {
#define MS_Type(type) type
        MS_Types
#undef MS_Type
    };

private:
    static const char *s_typeNames[];
    static const char *s_subsystemNames[];
private:
    static std::ofstream *s_logFile;
public:
    static void setLogFile(std::string path);
    static void closeLogFile();
public:
    static void message(const char *system, MessageType type, std::string msg);
};

}  // namespace Kriti

#define Message(msg) \
    Message3(General, Log, msg)

#define Message2(type, msg) \
    Message3(General, type, msg)

#define Message3(sys, type, msg) \
    do { \
        Kriti::MessageSystem::message(\
            #sys, \
            Kriti::MessageSystem::type,\
            Kriti::StreamAsString() << msg); \
    } while(0)

#endif
