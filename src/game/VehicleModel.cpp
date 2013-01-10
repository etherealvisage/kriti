#include "VehicleModel.h"

namespace Kriti {
namespace Game {

void VehicleModel::VehicleFeedback::updateTransform(Math::Vector location,
    Math::Quaternion orientation) {

    
}

void VehicleModel::addVehicle(boost::shared_ptr<Vehicle> vehicle) {
    m_vehicles.push_back(vehicle);
}

void VehicleModel::modify(boost::shared_ptr<Physics::World> world,
    btScalar step) {
    
    for(auto vehicle : m_vehicles) simulate(world, vehicle);
}

void VehicleModel::simulate(boost::shared_ptr<Physics::World> world,
    boost::shared_ptr<Vehicle> vehicle) {

    /*auto centre = vehicle->object()->
    
    world->rayCast(*/
}

}  // namespace Game
}  // namespace Kriti
