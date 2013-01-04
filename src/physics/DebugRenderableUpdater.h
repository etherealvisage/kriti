#ifndef KRITI_PHYSICS__DEBUG_RENDERABLE_UPDATER_H
#define KRITI_PHYSICS__DEBUG_RENDERABLE_UPDATER_H

#include <boost/shared_ptr.hpp>

#include <LinearMath/btIDebugDraw.h>

#include "render/Renderable.h"

namespace Kriti {
namespace Physics {

class DebugRenderableUpdater : public btIDebugDraw {
private:
    int m_debugMode;
    std::vector<Math::Vector> m_vertices;
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    DebugRenderableUpdater();
    ~DebugRenderableUpdater();

    boost::shared_ptr<Render::Renderable> renderable() { return m_renderable; }

    void updateRenderable();

    virtual void drawLine(const btVector3 &from, const btVector3 &to,
        const btVector3 &color);
    virtual void drawLine(const btVector3 &from, const btVector3 &to,
        const btVector3 &fromColour, const btVector3 &toColour) {}

    virtual void drawContactPoint(const btVector3 &pointOnB,
        const btVector3 &normalOnB, btScalar distance, int lifeTime,
        const btVector3 &color) {}
    
    virtual void reportErrorWarning(const char *warningString) {}
    virtual void draw3dText(const btVector3 &location,
        const char *textString) {}
    
    virtual void setDebugMode(int debugMode) { m_debugMode = debugMode; }
    virtual int getDebugMode() const { return m_debugMode; }

};

}  // namespace Physics
}  // namespace Kriti

#endif
