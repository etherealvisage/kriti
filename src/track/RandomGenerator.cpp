#include <queue>
#include <boost/make_shared.hpp>

#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include "RandomGenerator.h"

#include "math/Constants.h"
#include "math/Quaternion.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

RandomGenerator::RandomGenerator(int seed) : m_seed(seed) {
    m_gen = new boost::mt19937(seed);
}

void RandomGenerator::build() {
    std::queue<Node::Ptr> heads;
    heads.push(m_root->next()[0]);

    double cutoff = 10000.0;

    while(heads.size() > 0) {
        auto next = heads.front();
        //Message3(Track, Debug, "Head: " << next->position().toString());
        heads.pop();

        // don't grow any more if past the cutoff . . .
        if(std::fabs(next->position().z()) > cutoff) {
            Message3(Track, Debug, "Head is past cutoff.");
            continue;
        }

        int choice = rint(0, 99);

        // 10% chance to reorder (ignore current)
        // 9% chance to join (becomes split if only one path)
        // 11% chance to split (create new)
        // 70% chance to extend
        if(choice < 10 && heads.size() > 1) {
            heads.push(next);
        }
        else if(choice < 19 && heads.size() >= 2) {
            // join
            auto next2 = heads.front();
            heads.pop();

            auto centre = (next->position() + next2->position())/2;
            if(centre.z() < next->position().z()) {
                centre.setZ(next->position().z() + 1);
            }
            if(centre.z() < next2->position().z()) {
                centre.setZ(next2->position().z() + 1);
            }
            auto jp = centre + delta(1.0);

            auto n = boost::make_shared<Node>(jp);

            n->addPrev(next);
            n->addPrev(next2);

            next->addNext(n);
            next2->addNext(n);

            heads.push(n);
        }
        else if(choice < 30 && heads.size() < 15) {
            // split
            auto off = delta(2.0);
            auto roff = Math::Vector(-off.x(), -off.y(), off.z());

            auto n = boost::make_shared<Node>(next->position() + off);
            auto n2 = boost::make_shared<Node>(next->position() + roff);

            n->addPrev(next);
            n2->addPrev(next);

            next->addNext(n);
            next->addNext(n2);

            heads.push(n);
            heads.push(n2);
        }
        else {
            // grow
            auto n = boost::make_shared<Node>(next->position() + delta(1.0));

            n->addPrev(next);
            next->addNext(n);
            heads.push(n);
        }
    }

    Message3(Track, Debug, "Generated!");
}

int RandomGenerator::rint(int min, int max) {
    boost::random::uniform_int_distribution<> dist(min, max);
    return dist(*m_gen);
}

double RandomGenerator::rdouble(double min, double max) {
    boost::random::uniform_real_distribution<> dist(min, max);
    return dist(*m_gen);
}

double RandomGenerator::rdouble(double range) {
    boost::random::uniform_real_distribution<> dist(-range, range);
    return dist(*m_gen);
}

Math::Vector RandomGenerator::delta(double angleFactor) {
    Math::Vector axis(rdouble(1.0), rdouble(1.0), rdouble(1.0));
    axis = axis.normalized();
    double angle = rdouble(Math::Constants::Pi * angleFactor / 3);

    auto rotated = Math::Quaternion(axis, angle)
        * Math::Vector(0.0, 0.0, rdouble(1, 100));

    if(rotated.z() > 0) rotated.setZ(-rotated.z());
    rotated.setY(rotated.y()/4);
    return rotated;
}

}  // namespace Track
}  // namespace Kriti
