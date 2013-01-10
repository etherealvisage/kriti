#ifndef KRITI_GAME__VEHICLE_SUSPENSION_H
#define KRITI_GAME__VEHICLE_SUSPENSION_H

#include "math/Vector.h"

namespace Kriti {
namespace Game {

class VehicleSuspension {
private:
    Math::Vector m_offset, m_direction;
    double m_springK, m_restLength;

    double m_distance;
public:
    VehicleSuspension(Math::Vector offset, Math::Vector direction,
        double springK, double restLength) : m_offset(offset),
        m_direction(direction), m_springK(springK), m_restLength(restLength),
        m_distance(0.0) {}

    Math::Vector offset() const { return m_offset; }
    Math::Vector direction() const { return m_direction; }

    double springK() const { return m_springK; }
    double restLength() const { return m_restLength; }

    void setDistance(double distance) { m_distance = distance; }
    double distance() const { return m_distance; }
};

}  // namespace Game
}  // namespace Kriti

#endif
