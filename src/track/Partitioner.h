#ifndef KRITI_TRACK__PARTITIONER_H
#define KRITI_TRACK__PARTITIONER_H

#include <vector>
#include <set>

#include "Node.h"

namespace Kriti {
namespace Track {

class Partitioner {
public:
    std::vector<std::vector<Node::Ptr>> partition(Node::Ptr root);
private:
    void partitionHelper(std::vector<std::vector<Node::Ptr>> &paths,
        std::set<Node::Ptr> &visited, std::vector<Node::Ptr> &current,
        Node::Ptr n);
};

}  // namespace Track
}  // namespace Kriti

#endif
