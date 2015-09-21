#ifndef KRITI__TUPLE_UTIL_H
#define KRITI__TUPLE_UTIL_H

#include <boost/function.hpp>
#include <boost/tuple/tuple.hpp>

namespace Kriti {
namespace TupleUtil {

template<typename R, typename ...T>
R apply(const boost::function<R (T...)> &function,
    const boost::tuple<T...> &params);

template<typename R>
R apply(const boost::function<R ()> &function, const boost::tuple<> &) {
    return function();
}

template<typename R, typename P1>
R apply(const boost::function<R (P1)> &function,
    const boost::tuple<P1> &params) {

    return function(boost::get<0>(params));
}

template<typename R, typename P1, typename P2>
R apply(const boost::function<R (P1, P2)> &function,
    const boost::tuple<P1, P2> &params) {

    return function(boost::get<0>(params), boost::get<1>(params));
}

template<typename R, typename P1, typename P2, typename P3>
R apply(const boost::function<R (P1, P2, P3)> &function,
    const boost::tuple<P1, P2, P3> &params) {

    return function(boost::get<0>(params), boost::get<1>(params),
        boost::get<2>(params));
}

template<typename R, typename P1, typename P2, typename P3, typename P4>
R apply(const boost::function<R (P1, P2, P3, P4)> &function,
    const boost::tuple<P1, P2, P3, P4> &params) {

    return function(boost::get<0>(params), boost::get<1>(params),
        boost::get<2>(params), boost::get<3>(params));
}

template<typename R, typename P1, typename P2, typename P3, typename P4,
    typename P5>
R apply(const boost::function<R (P1, P2, P3, P4, P5)> &function,
    const boost::tuple<P1, P2, P3, P4, P5> &params) {

    return function(boost::get<0>(params), boost::get<1>(params),
        boost::get<2>(params), boost::get<3>(params), boost::get<4>(params));
}

}  // namespace TupleUtil
}  // namespace Kriti

#endif
