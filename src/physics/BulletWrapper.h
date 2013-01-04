#ifndef KRITI_PHYSICS__BULLET_WRAPPER_H
#define KRITI_PHYSICS__BULLET_WRAPPER_H

#include <set>

#include <boost/shared_ptr.hpp>

#include <btBulletDynamicsCommon.h>

#include "ObjectManipulator.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace Kriti {

// forward decls
namespace Render {
class Pipeline;
class Renderable;
}

namespace Physics {

class DebugRenderableUpdater;

class BulletWrapper {
private:
    static boost::shared_ptr<BulletWrapper> s_singleton;
public:
    static boost::shared_ptr<BulletWrapper> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<BulletWrapper>(
                new BulletWrapper());
        }
        return s_singleton;
    }

    static void destroy() {
        s_singleton.reset();
    }
private:
    BulletWrapper();

    boost::shared_ptr<btBroadphaseInterface> m_bpInterface;
    boost::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfig;
    boost::shared_ptr<btCollisionDispatcher> m_collisionDispatcher;
    boost::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
    boost::shared_ptr<btDiscreteDynamicsWorld> m_world;

    std::set<boost::shared_ptr<ObjectManipulator>> m_manipulators;

    DebugRenderableUpdater *m_updater;
public:
    ~BulletWrapper();

    boost::shared_ptr<btDiscreteDynamicsWorld> world() const
        { return m_world; }

    void addObjectManipulator(
        boost::shared_ptr<ObjectManipulator> manipulator);
    void removeObjectManipulator(
        boost::shared_ptr<ObjectManipulator> manipulator);

    boost::shared_ptr<Render::Renderable> debugRenderable();
    void updateDebugRenderable();
    void stepWorld(int usec);
private:
    static void step(btDynamicsWorld *world, btScalar passed);
};

}  // namespace Physics
}  // namespace Kriti

#endif
