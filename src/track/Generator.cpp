#include <map>

#include <boost/make_shared.hpp>

#include "Generator.h"
#include "Partitioner.h"

#include "MessageSystem.h"
#include "TimeValue.h"

namespace Kriti {
namespace Track {

boost::shared_ptr<ExtrusionResult> Generator::generate(Subdivider *subdivider,
    Extruder *extruder) {

    TimeValue before = TimeValue::current();
    seed();
    build();
    subdivide(subdivider);
    extrude(extruder);
    TimeValue after = TimeValue::current();
    Message3(Track, Log, "Generated track geometry in "
        << (after - before).toMsec() << " ms.");

    return m_result;
}

void Generator::seed() {
    m_root = boost::make_shared<Node>(Math::Vector());
    auto initial = boost::make_shared<Node>(
        Math::Vector(0.0, 0.0, -50.0));

    m_root->addNext(initial);
    initial->addPrev(m_root);

#if 0
    auto left = boost::make_shared<Node>(
        Math::Vector(-50.0, 20.0, -100.0));
    auto right = boost::make_shared<Node>(
        Math::Vector(50.0, 20.0, -100.0));

    left->addPrev(initial);
    right->addPrev(initial);

    initial->addNext(left);
    initial->addNext(right);

    auto left2 = boost::make_shared<Node>(
        Math::Vector(-50.0, 20.0, -150.0));
    auto right2 = boost::make_shared<Node>(
        Math::Vector(50.0, 20.0, -150.0));

    left2->addPrev(left);
    right2->addPrev(right2);

    left->addNext(left2);
    right->addNext(right2);

    auto left3 = boost::make_shared<Node>(
        Math::Vector(-25.0, 30.0, -200.0));
    auto right3 = boost::make_shared<Node>(
        Math::Vector(25.0, 30.0, -200.0));

    left3->addPrev(left2);
    right3->addPrev(left3);

    left2->addNext(left3);
    right2->addNext(right3);

    auto join = boost::make_shared<Node>(
        Math::Vector(0.0, 20.0, -250.0));

    join->addPrev(left3);
    join->addPrev(right3);

    left3->addNext(join);
    right3->addNext(join);

    auto tail = boost::make_shared<Node>(
        Math::Vector(0.0, 10.0, -275.0));

    tail->addPrev(join);
    join->addNext(tail);
#endif
}

void Generator::subdivide(Subdivider *subdivider) {
    Track::Partitioner partitioner;
    auto paths = partitioner.partition(m_root);
    auto newRoot = boost::make_shared<Node>(m_root->position());

    std::map<Node::Ptr, Node::Ptr> iso;
    iso[m_root] = newRoot;
    for(auto path : paths) {
        Node::Ptr nstart, nend;
        subdivider->subdivide(path, nstart, nend);

        if(iso.find(path.front()) == iso.end()) {
            iso[path.front()] = nstart;
        }
        else {
            auto nn = nstart->next()[0];
            nn->prev().clear();
            nn->addPrev(iso[path.front()]);
            iso[path.front()]->addNext(nn);
        }

        if(iso.find(path.back()) == iso.end()) {
            iso[path.back()] = nend;
        }
        else {
            auto np = nend->prev()[0];
            auto last = path[path.size()-1];
            np->next().clear();
            np->addNext(iso[last]);
            iso[last]->addPrev(np);
        }
    }

    m_root = newRoot;
}

void Generator::extrude(Extruder *extruder) {
    m_result = extruder->extrude(m_root);
}

}  // namespace Track
}  // namespace Kriti
