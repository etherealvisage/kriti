#include "TupleUtil.h"

namespace Kriti {

void test() {
    boost::function<void (int)> f;
    TupleUtil::apply(f, boost::tuple<int>(1));
}

}  // namespace Kriti
