#ifndef KRITI_TRACK__EXTRUDER_H
#define KRITI_TRACK__EXTRUDER_H

#include <utility>

#include "Node.h"
#include "ExtrusionResult.h"

namespace Kriti {
namespace Track {

class Extruder {
public:
    virtual boost::shared_ptr<ExtrusionResult> extrude(Node::Ptr root) = 0;
};

}  // namespace Track
}  // namespace Kriti

#endif
