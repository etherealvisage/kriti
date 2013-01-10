#ifndef KRITI_GAME__VEHICLE_H
#define KRITI_GAME__VEHICLE_H

#include <boost/shared_ptr.hpp>

#include "VehicleSuspension.h"

#include "physics/PhysicalObject.h"

#include "math/Vector.h"

namespace Kriti {
namespace Game {

class Vehicle {
private:
    boost::shared_ptr<Physics::PhysicalObject> m_object;

    double m_turning;
    double m_acceleration;

    std::vector<VehicleSuspension> m_suspensions;
public:
    Vehicle(boost::shared_ptr<Physics::PhysicalObject> object)
        : m_object(object), m_turning(0.0), m_acceleration(0.0) {}
    ~Vehicle() {}

    boost::shared_ptr<Physics::PhysicalObject> object() const
        { return m_object; }

    double turning() const { return m_turning; }
    double acceleration() const { return m_acceleration; }

    void addSuspension(VehicleSuspension suspension)
        { m_suspensions.push_back(suspension); }
    const VehicleSuspension &suspension(int index) const
        { return m_suspensions[index]; }
    VehicleSuspension &suspension(int index) { return m_suspensions[index]; }
    int suspensionCount() const { return m_suspensions.size(); }
};

}  // namespace Game
}  // namespace Kriti

#endif
