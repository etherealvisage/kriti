#include <boost/make_shared.hpp>

#include "Object.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void Object::Updater::transformUpdated(Math::Vector location,
    Math::Quaternion orientation) {

    //Message3(Game, Debug, "Moving renderable to " << location.toString());
    m_object->m_renderable->location() = location;
    m_object->m_renderable->orientation() = orientation;
}

Object::Object() {
}

Object::~Object() {
    
}

void Object::setPhysical(boost::shared_ptr<Physics::PhysicalObject> phy) {
    m_physical = phy;
    m_physical->addFeedback(boost::make_shared<Updater>(this));
}

}  // namespace Game
}  // namespace Kriti
