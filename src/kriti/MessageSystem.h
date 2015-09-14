#ifndef KRITI__MESSAGE_SYSTEM_H
#define KRITI__MESSAGE_SYSTEM_H

#include <iosfwd>

#include "StreamAsString.h"

#define MS_Subsystems \
    MS_Subsystem(General), \
    MS_Subsystem(Math), \
    MS_Subsystem(Config), \
    MS_Subsystem(Interface), \
    MS_Subsystem(Render), \
    MS_Subsystem(Physics), \
    MS_Subsystem(Game), \
    MS_Subsystem(Track), \
    MS_Subsystem(GUI), \
    MS_Subsystem(Profile), \
    MS_Subsystem(Assimp), \
    MS_Subsystem(Scene)

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

    enum Subsystem {
#define MS_Subsystem(system) system
        MS_Subsystems
#undef MS_Subsystem
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
    static void message(Subsystem system, MessageType type, std::string msg);
};

}  // namespace Kriti

#define Message(msg) \
    Message3(General, Log, msg)

#define Message2(type, msg) \
    Message3(General, type, msg)

#define Message3(sys, type, msg) \
    Kriti::MessageSystem::message(\
        Kriti::MessageSystem::sys,\
        Kriti::MessageSystem::type,\
        Kriti::StreamAsString() << msg)

#endif
