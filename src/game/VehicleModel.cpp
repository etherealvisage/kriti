#include "VehicleModel.h"

#include "physics/World.h"

#include "track/Partitioner.h"

#include "math/Geometry.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void VehicleModel::setRoot(boost::shared_ptr<Track::Node> root) {
    m_edges.clear();
    m_root = root;

    // TODO: make this use some sort of spatial data structure . . .
    auto paths = Track::Partitioner().partition(root);

    for(auto path : paths) {
        for(unsigned i = 1; i < path.size(); i ++) {
            m_edges.push_back(std::make_pair(
                path[i-1]->position(), path[i]->position()));
        }
    }

    Message3(Game, Debug, "There are " << m_edges.size() << " edges.");
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

    double closest = 1e100;
    for(auto edge : m_edges) {
        auto diff = vehicle->location() -
            Math::Geometry::closestSegmentPoint(edge.first, edge.second,
                vehicle->location());
        closest = std::min(closest, diff.dot(diff));
    }

    // TODO: make maximum force, modifier, etc. configurable.
    double force = 1 / (std::max(0.05, std::sqrt(closest)));

    vehicle->object()->applyForce(Math::Vector(0.0, 0.0, -force));

    // now for roll/yaw/pitch modifiers . . .
    /*vehicle->object()->applyTorque(vehicle->orientation() *
        (Math::Vector(1.0, 0.0, 0.0) * vehicle->pitch()));*/
    vehicle->object()->applyTorque(Math::Vector(vehicle->pitch(), 0.0, 0.0));
}

}  // namespace Game
}  // namespace Kriti
