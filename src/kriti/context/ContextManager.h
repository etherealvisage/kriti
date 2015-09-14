#ifndef KRITI_CONTEXT__CONTEXT_MANAGER_H
#define KRITI_CONTEXT__CONTEXT_MANAGER_H

#include <map>
#include <vector>

#include "AbstractContext.h"

namespace Kriti {
namespace Context {

class ContextManager {
private:
    static ContextManager *s_singleton;
public:
    static ContextManager *instance() {
        if(!s_singleton) s_singleton = new ContextManager();
        return s_singleton;
    }
    static void destroy() {
        delete s_singleton;
    }
private:
    std::map<std::string, AbstractContext *> m_contextMap;
    std::vector<AbstractContext *> m_contextStack;
private:
    ContextManager() {}
public:
    void addContext(AbstractContext *context);

    void pushContext(std::string name);
    void popContext();

    void loop();
};

}  // namespace Context
}  // namespace Kriti

#endif
