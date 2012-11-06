#include <cstring>
#include <ctime>

#include <boost/filesystem.hpp>

#include "MessageSystem.h"

namespace Kriti {

std::ofstream *MessageSystem::s_logFile;

const char *MessageSystem::s_typeNames[] = {
#define MS_Type(type) #type
    MS_Types
#undef MS_Type
};

const char *MessageSystem::s_subsystemNames[] = {
#define MS_Subsystem(system) #system
    MS_Subsystems
#undef MS_Subsystem
};

void MessageSystem::setLogFile(std::string path) {
    std::string::size_type pos;
    if((pos = path.find("%d")) != std::string::npos) {
        // TODO: binary search this.
        char buf[1000];
        std::string s;
        for(int i = 0; i < 10000; i ++) {
            std::sprintf(buf, "%05d", i);
            s = path;
            s.replace(pos, 2, buf);

            if(!boost::filesystem::exists(s)) break;
        }
        path = s;
    }

    Message3(Config, Log, "Opening log file " << path);
    s_logFile = new std::ofstream(path.c_str());
}

void MessageSystem::closeLogFile() {
    if(s_logFile) {
        delete s_logFile;
        s_logFile = NULL;
    }
}

void MessageSystem::message(Subsystem system, MessageType type,
    std::string msg) {

    std::time_t t;
    std::time(&t);

    struct tm *lt = std::localtime(&t);

    char buffer[4096];
    std::snprintf(buffer, sizeof(buffer),
        "[%02i:%02i:%02i %-12s %-7s]        %s\n",
        lt->tm_hour, lt->tm_min, lt->tm_sec,
        s_subsystemNames[system], s_typeNames[type],
        msg.c_str());

    printf("%s", buffer);
    if(s_logFile != NULL) {
        (*s_logFile) << buffer;
    }
    
    if(type == Fatal) {
        closeLogFile();
        std::abort();
    }
}

}  // namespace Kriti
