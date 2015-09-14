#ifndef KRITI_GAME__OBJECT_H
#define KRITI_GAME__OBJECT_H

#include <boost/shared_ptr.hpp>

#include "../render/Renderable.h"
#include "../physics/PhysicalObject.h"
#include "../physics/ObjectFeedback.h"

namespace Kriti {
namespace Game {

class Object {
private:
    class Updater : public Physics::ObjectFeedback {
    private:
        Object *m_object;
    public:
        Updater(Object *object) : m_object(object) {}
        virtual ~Updater() {}

        virtual void transformUpdated(Math::Vector location,
            Math::Quaternion rotation);
    };
private:
    boost::shared_ptr<Physics::PhysicalObject> m_physical;
    boost::shared_ptr<Render::Renderable> m_renderable;
public:
    Object();
    ~Object();

    boost::shared_ptr<Physics::PhysicalObject> physical()
	const { return m_physical; }
    
    boost::shared_ptr<Render::Renderable> renderable()
	const { return m_renderable; }

    void setPhysical(boost::shared_ptr<Physics::PhysicalObject> phy);
    void setRenderable(boost::shared_ptr<Render::Renderable> render)
        { m_renderable = render; }
};

}  // namespace Game
}  // namespace Kriti

#endif
