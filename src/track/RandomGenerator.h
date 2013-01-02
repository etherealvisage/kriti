#ifndef KRITI_TRACK__RANDOM_GENERATOR_H
#define KRITI_TRACK__RANDOM_GENERATOR_H

#include <boost/random/mersenne_twister.hpp>

#include "Generator.h"

namespace Kriti {
namespace Track {

class RandomGenerator : public Generator {
private:
    int m_seed;
    boost::mt19937 *m_gen;
public:
    RandomGenerator(int seed);
protected:
    virtual void build();
private:
    int rint(int min, int max);
    double rdouble(double min, double max);
    double rdouble(double range);
    Math::Vector delta(double angleFactor);
};

}  // namespace Track
}  // namespace Kriti

#endif
