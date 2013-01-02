#include "Partitioner.h"

#include "MessageSystem.h"

namespace Kriti {
namespace Track {

std::vector<std::vector<Node::Ptr>> Partitioner::partition(Node::Ptr root) {
    std::vector<std::vector<Node::Ptr>> paths;
    std::set<Node::Ptr> visited;

    std::vector<Node::Ptr> ip;
    partitionHelper(paths, visited, ip, root);
    
    return paths;
}

void Partitioner::partitionHelper(std::vector<std::vector<Node::Ptr>> &paths,
    std::set<Node::Ptr> &visited, std::vector<Node::Ptr> &current,
    Node::Ptr n) {

    current.push_back(n);

    // finished with the current path?
    if(visited.find(n) != visited.end() || n->next().size() == 0) {
        paths.push_back(current);
        return;
    }

    visited.insert(n);
    if(n->next().size() == 1 && n->prev().size() <= 1) {
        partitionHelper(paths, visited, current, n->next()[0]);
    }
    else {
        paths.push_back(current);
        for(unsigned i = 0; i < n->next().size(); i ++) {
            std::vector<Node::Ptr> p;
            p.push_back(n);
            partitionHelper(paths, visited, p, n->next()[i]);
        }
    }
}

}  // namespace Track
}  // namespace Kriti
