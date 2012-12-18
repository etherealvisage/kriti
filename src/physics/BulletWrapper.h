#ifndef KRITI_PHYSICS__BULLET_WRAPPER_H
#define KRITI_PHYSICS__BULLET_WRAPPER_H

#include <boost/shared_ptr.hpp>

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

namespace Kriti {
namespace Physics {

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
public:
    ~BulletWrapper();

    boost::shared_ptr<btDiscreteDynamicsWorld> world() const
        { return m_world; }

    void stepWorld(int usec);
};

}  // namespace Physics
}  // namespace Kriti

#endif
