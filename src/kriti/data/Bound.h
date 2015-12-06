#ifndef KRITI_DATA__BOUND_H
#define KRITI_DATA__BOUND_H

#include <iostream>
#include <stdarg.h>
#include <algorithm>

#include <boost/serialization/access.hpp>

#include "Point.h"

namespace Kriti {
namespace Data {

template<typename Key, int Dimensions>
class Bound {
private:
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive &ar, const unsigned version) {
        ar & m_bounds;
    }
private:
    bool m_initialized;
    Key m_bounds[Dimensions][2];
public:
    Bound() {
        for(int i = 0; i < Dimensions; i ++) {
            m_bounds[i][0] = m_bounds[i][1] = 0.0;
        }
        m_initialized = false;
    }
    Bound(Key d1_start, Key d1_end, ...) {
        va_list ap;
        va_start(ap, d1_end);

        m_bounds[0][0] = d1_start, m_bounds[0][1] = d1_end;

        for(int i = 1; i < Dimensions; i ++) {
            m_bounds[i][0] = va_arg(ap, Key);
            m_bounds[i][1] = va_arg(ap, Key);
        }

        va_end(ap);
        m_initialized = false;
    }
    
    bool initialized() const { return m_initialized; }
    Key &start(int dimension) { return m_bounds[dimension][0]; }
    Key start(int dimension) const { return m_bounds[dimension][0]; }
    Key &end(int dimension) { return m_bounds[dimension][1]; }
    Key end(int dimension) const { return m_bounds[dimension][1]; }
    
    bool overlaps(const Bound &other) const {
        if(!m_initialized) return false;

        for(int i = 0; i < Dimensions; i ++) {
            if(m_bounds[i][0] > other.m_bounds[i][1] ||
                m_bounds[i][1] < other.m_bounds[i][0]) return false;
        }
        return true;
    }
    
    bool contains(const Point<Key, Dimensions> &point) {
        if(!m_initialized) return false;

        for(int i = 0; i < Dimensions; i ++) {
            if(m_bounds[i][0] > point.coordinate(i) ||
                m_bounds[i][1] < point.coordinate(i)) return false;
        }
        return true;
    }
    
    Key toCover(const Bound &other) {
        if(!m_initialized) return 0;

        Key volume = 0;
        Key bounds[Dimensions][2];
        Key sizes[Dimensions];
        
        for(int i = 0; i < Dimensions; i ++) {
            bounds[i][0] = m_bounds[i][0];
            bounds[i][1] = m_bounds[i][1];
            sizes[i] = m_bounds[i][1] - m_bounds[i][0];
        }
        
        for(int i = 0; i < Dimensions; i ++) {
            Key delta = 0;
            if(other.m_bounds[i][0] < bounds[i][0]) delta += bounds[i][0] - other.m_bounds[i][0];
            if(other.m_bounds[i][1] > bounds[i][1]) delta += other.m_bounds[i][1] - bounds[i][1];
            sizes[i] += delta;
            
            for(int i = 0; i < Dimensions; i ++) {
                volume += delta*sizes[i];
            }
        }
        return volume;
    }
    
    void cover(const Bound &other) {
        if(!m_initialized) *this = other;

        for(int i = 0; i < Dimensions; i ++) {
            m_bounds[i][0] = std::min(m_bounds[i][0], other.m_bounds[i][0]);
            m_bounds[i][1] = std::max(m_bounds[i][1], other.m_bounds[i][1]);
        }
    }

    Key volume() const {
        Key value = m_bounds[0][1] - m_bounds[0][0];
        for(int i = 1; i < Dimensions && value != 0; i ++) {
            value *= (m_bounds[i][1] - m_bounds[i][0]);
        }
        return value;
    }
};

}  // namespace Data
}  // namespace Kriti

#endif
