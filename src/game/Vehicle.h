#ifndef KRITI_GAME__VEHICLE_H
#define KRITI_GAME__VEHICLE_H

#include <boost/shared_ptr.hpp>

#include "VehicleSuspension.h"

#include "physics/PhysicalObject.h"
#include "physics/ObjectFeedback.h"

#include "math/Vector.h"

namespace Kriti {
namespace Game {

class Vehicle {
private:
    class VehicleFeedback : public Physics::ObjectFeedback {
    private:
        Vehicle *m_vehicle;
    public:
        VehicleFeedback(Vehicle *vehicle) : m_vehicle(vehicle) {}
    protected:
        virtual void transformUpdated(Math::Vector location,
            Math::Quaternion orientation);
    };
private:
    boost::shared_ptr<Physics::PhysicalObject> m_object;

    boost::shared_ptr<VehicleFeedback> m_feedback;
    Math::Vector m_location;
    Math::Quaternion m_orientation;

    double m_turning;
    double m_acceleration;

    std::vector<VehicleSuspension> m_suspensions;
public:
    Vehicle(boost::shared_ptr<Physics::PhysicalObject> object);
    ~Vehicle();

    boost::shared_ptr<Physics::PhysicalObject> object() const
        { return m_object; }

    Math::Vector location() const { return m_location; }
    Math::Quaternion orientation() const { return m_orientation; }

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
