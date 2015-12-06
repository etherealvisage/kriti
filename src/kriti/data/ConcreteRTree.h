#ifndef KRITI_DATA__CONCRETE_RTREE_H
#define KRITI_DATA__CONCRETE_RTREE_H

#include <boost/function.hpp>

#include "RTree.h"

#include "../math/Vector.h"

namespace Kriti {
namespace Data {

template<typename DataType>
class ConcreteRTree {
public:
    typedef boost::function<void (Math::Vector, Math::Vector, DataType)>
        CallbackType;
private:
    typedef RTree<double, DataType, 3> TreeType;
private:
    TreeType m_tree;
public:
    void search(Math::Vector begin, Math::Vector end,
        CallbackType callback) {

        m_tree.search(bound(begin, end), TreeType::SearchCallbackType(
            [=](typename TreeType::BoundType bounds, DataType data){
                callback(start(bounds), end(bounds), data);
            }));
    }

    void searchRay(Math::Vector begin, Math::Vector direction,
        CallbackType callback) {

        m_tree.search(point(begin), point(direction),
            TreeType::SearchCallbackType([=](
                typename TreeType::BoundType bounds, DataType data){
                    callback(start(bounds), end(bounds), data);
                }));
    }

    void insert(Math::Vector begin, Math::Vector end, DataType d) {
        m_tree.insert(bound(begin, end), d);
    }

    void remove(Math::Vector begin, Math::Vector end, DataType d) {
        m_tree.remove(bound(begin, end), d);
    }
private:
    static typename TreeType::PointType point(const Math::Vector &pt) {

        return TreeType::PointType(pt.x(), pt.y(), pt.z());
    }

    static typename TreeType::BoundType bound(const Math::Vector &begin,
        const Math::Vector &end) {

        return TreeType::BoundType(begin.x(), end.x(), begin.y(), end.y(),
            begin.z(), end.z());
    }

    static Math::Vector start(const typename TreeType::BoundType &bound) {
        return Math::Vector(bound.start(0), bound.start(1), bound.start(2));
    }

    static Math::Vector end(const typename TreeType::BoundType &bound) {
        return Math::Vector(bound.end(0), bound.end(1), bound.end(2));
    }
};

}  // namespace Data
}  // namespace Kriti

#endif
