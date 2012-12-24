#ifndef KRITI_GAME__OBJECT_H
#define KRITI_GAME__OBJECT_H

#include <boost/shared_ptr.hpp>

#include "render/Renderable.h"
#include "physics/PhysicalObject.h"

namespace Kriti {
namespace Game {

class Object {
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

    void setPhysical(boost::shared_ptr<Physics::PhysicalObject> phy)
        { m_physical = phy; }
    void setRenderable(boost::shared_ptr<Render::Renderable> render)
        { m_renderable = render; }

    void updateRenderableFromPhysical();
};

}  // namespace Game
}  // namespace Kriti

#endif
