#include <vector>

#include <boost/make_shared.hpp>

#include "ClosedSubdivider.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

ClosedSubdivider::ClosedSubdivider(int depth) {
    if(depth < 1) {
        Message3(Track, Warning, "Resetting subdivision depth to 1.");
        depth = 1;
    }
    m_depth = depth;
}

void ClosedSubdivider::subdivide(const std::vector<Node::Ptr> &path,
    Node::Ptr &nstart, Node::Ptr &nend) {

    std::vector<Math::Vector> points;
    for(auto p : path) {
        points.push_back(p->position());
    }

    for(int i = 0; i < m_depth; i ++) subdivide(points);

    nstart = boost::make_shared<Node>(points[0]);
    auto prev = nstart;
    for(unsigned i = 1; i < points.size(); i ++) {
        auto next = boost::make_shared<Node>(points[i]);
        next->addPrev(prev);
        prev->addNext(next);
        prev = next;
    }
    nend = prev;
}

void ClosedSubdivider::subdivide(std::vector<Math::Vector> &points) {
    std::vector<Math::Vector> fine;

    // handle this case specially.
    if(points.size() < 2) {
        Message3(Track, Error, "Trying to subdivide only one point!");
    }
    else if(points.size() == 2) {
        auto v1 = points.front();
        auto v2 = points.back();
        points.pop_back();
        points.push_back((v1+v2)/2);
        points.push_back(v2);
        return;
    }
    fine.push_back(points.front());
    fine.push_back((points.front() + points[1])/2);

    for(unsigned i = 1; i+2 < points.size(); i ++) {
        fine.push_back(points[i]*.75 + points[i+1]*.25);
        fine.push_back(points[i]*.25 + points[i+1]*.75);
    }

    fine.push_back((points.back() + points[points.size()-2])/2);
    fine.push_back(points.back());

    points.swap(fine);
}

}  // namespace Track
}  // namespace Kriti
