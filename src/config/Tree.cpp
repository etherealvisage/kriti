#include <boost/algorithm/string.hpp>

#include "Tree.h"

namespace Kriti {
namespace Config {

Tree::Tree() {
    m_root = boost::shared_ptr<TreeNode>(new TreeNode("root"));
}

Tree::~Tree() {
    
}

boost::weak_ptr<TreeNode> Tree::node(const std::string &path) {
    boost::weak_ptr<TreeNode> cursor = m_root, prev = cursor;

    std::vector<std::string> nodeNames;

    boost::algorithm::split(
        nodeNames,
        path,
        boost::algorithm::is_any_of("."),
        boost::algorithm::token_compress_on
    );

    for(auto n : nodeNames) {
        prev = cursor;
        cursor = cursor.lock()->child(n);
        if(cursor.expired()) {
            cursor = prev.lock()->addChild(n);
        }
    }

    return cursor;
}

boost::weak_ptr<TreeNode> Tree::node(const std::string &path) const {
    boost::weak_ptr<TreeNode> cursor = m_root;

    std::vector<std::string> nodeNames;

    boost::algorithm::split(
        nodeNames,
        path,
        boost::algorithm::is_any_of("."),
        boost::algorithm::token_compress_on
    );

    for(auto n : nodeNames) {
        if(cursor.expired()) return boost::weak_ptr<TreeNode>();

        cursor = cursor.lock()->child(n);
    }

    return cursor;
}

}  // namespace Config
}  // namespace Kriti
