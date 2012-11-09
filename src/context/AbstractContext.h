#ifndef KRITI_CONTEXT__ABSTRACT_CONTEXT_H
#define KRITI_CONTEXT__ABSTRACT_CONTEXT_H

#include <string>

namespace Kriti {
namespace Context {

class AbstractContext {
public:
    enum ContextState {
        Deactivated,
        Activated
    };
private:
    bool m_activated;
public:
    AbstractContext() : m_activated(false) {}
    virtual ~AbstractContext() {}

    virtual std::string contextName() = 0;

    void activate() { m_activated = true; activateHook(); }
    void deactivate() { m_activated = false; deactivateHook(); }

    virtual void run() = 0;
protected:
    bool activated() const { return m_activated; }

    virtual void activateHook() = 0;
    virtual void deactivateHook() = 0;
};

}  // namespace Context
}  // namespace Kriti

#endif
