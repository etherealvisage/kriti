#ifndef KRITI_GAME__VEHICLE_H
#define KRITI_GAME__VEHICLE_H

#include <boost/shared_ptr.hpp>

#include "physics/PhysicalObject.h"
#include "physics/ObjectFeedback.h"

#include "math/Vector.h"

#include "MessageSystem.h"

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

    double m_yaw;
    double m_pitch;
    double m_roll;
    double m_braking;
public:
    Vehicle(boost::shared_ptr<Physics::PhysicalObject> object);
    ~Vehicle();

    boost::shared_ptr<Physics::PhysicalObject> object() const
        { return m_object; }

    Math::Vector location() const { return m_location; }
    Math::Quaternion orientation() const { return m_orientation; }

    double yaw() const { return m_yaw; }
    void setYaw(double yaw) { m_yaw = yaw; }

    double pitch() const { return m_pitch; }
    void setPitch(double pitch) { m_pitch = pitch; }

    double roll() const { return m_roll; }
    void setRoll(double roll) { m_roll = roll; }

    double braking() const { return m_braking; }
    void setBraking(double braking) { m_braking = braking; }
};

}  // namespace Game
}  // namespace Kriti

#endif
