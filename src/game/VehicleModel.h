#ifndef KRITI_GAME__VEHICLE_MODEL_H
#define KRITI_GAME__VEHICLE_MODEL_H

#include <boost/shared_ptr.hpp>

#include "physics/ObjectModifier.h"

#include "Vehicle.h"

namespace Kriti {
namespace Game {

class VehicleModel : public Physics::ObjectModifier {
private:
private:
    std::vector<boost::shared_ptr<Vehicle>> m_vehicles;
public:
    void addVehicle(boost::shared_ptr<Vehicle> vehicle);
protected:
    virtual void modify(boost::shared_ptr<Physics::World> world,
        btScalar step);
private:
    void simulate(boost::shared_ptr<Physics::World> world,
        boost::shared_ptr<Vehicle> vehicle);
};

}  // namespace Game
}  // namespace Kriti

#endif
