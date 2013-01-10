#include <boost/make_shared.hpp>

#include "Vehicle.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void Vehicle::VehicleFeedback::transformUpdated(Math::Vector location,
    Math::Quaternion orientation) {

    m_vehicle->m_location = location;
    m_vehicle->m_orientation = orientation;
}

Vehicle::Vehicle(boost::shared_ptr<Physics::PhysicalObject> object)
    : m_object(object), m_turning(0.0), m_acceleration(0.0) {

    m_feedback = boost::make_shared<VehicleFeedback>(this);
    object->addFeedback(m_feedback);
}

Vehicle::~Vehicle() {
    
}

}  // namespace Game
}  // namespace Kriti
