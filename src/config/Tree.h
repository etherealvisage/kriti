#ifndef KRITI_CONFIG__TREE_H
#define KRITI_CONFIG__TREE_H

#include <string>

#include "TreeNode.h"

namespace Kriti {
namespace Config {

class Tree {
private:
    boost::shared_ptr<TreeNode> m_root;
public:
    Tree();
    ~Tree();

    boost::weak_ptr<TreeNode> node(const std::string &path);
    boost::weak_ptr<TreeNode> node(const std::string &path) const;
};

}  // namespace Config
}  // namespace Kriti

#endif
