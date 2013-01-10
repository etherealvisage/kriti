#include "VehicleModel.h"

#include "physics/World.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Game {

void VehicleModel::addVehicle(boost::shared_ptr<Vehicle> vehicle) {
    m_vehicles.push_back(vehicle);
}

void VehicleModel::modify(boost::shared_ptr<Physics::World> world,
    btScalar step) {
    
    for(auto vehicle : m_vehicles) simulate(world, vehicle);
}

void VehicleModel::simulate(boost::shared_ptr<Physics::World> world,
    boost::shared_ptr<Vehicle> vehicle) {

    auto orientation = vehicle->orientation();
    for(int i = 0; i < vehicle->suspensionCount(); i ++) {
        auto suspension = vehicle->suspension(i);
        double distance;
        auto where = vehicle->location() + suspension.offset()*orientation;
        auto direction = (suspension.direction()*orientation).normalized();

        auto result = world->rayCast(where, where + direction, &distance);

        // no collision?
        if(!result) continue;

        double delta = suspension.restLength() - distance;
        //Message3(Game, Debug, "Distance: " << distance << " Delta: " << delta);
        if(delta > 0.0) {
            double f = delta*delta*suspension.springK();
            //Message3(Game, Debug, "f:" << f);
            vehicle->object()->applyForce(direction*10,
                -direction * f);
        }
    }

    Math::Vector forwards = orientation * Math::Vector(0.0, 0.0, -1.0);
    Math::Vector velocity = vehicle->object()->linearVelocity();
    double yvelocity = velocity.y();
    velocity.setY(0.0);

    if(velocity.length2() > Math::Constants::Epsilon) {
        Math::Vector proj = velocity.projectOnto(forwards);
        Math::Vector vdiff = velocity - proj;
        Message3(Game, Debug, "vdiff: " << vdiff.toString());
        vehicle->object()->applyForce(-vdiff/2.0);
    }

    if(yvelocity > Math::Constants::Epsilon) {
        vehicle->object()->applyForce(Math::Vector(0.0, -yvelocity/1.0));
    }

    // try to level the vehicle.
    /*Math::Vector up = (orientation * Math::Vector(0.0, 1.0, 0.0)).normalized();
    vehicle->object()->applyTorque(Math::Vector(-up.z()/10.0, 0.0, up.x()/10.0));*/
}

}  // namespace Game
}  // namespace Kriti
