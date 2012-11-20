#include <boost/algorithm/string.hpp>

#include "Tree.h"

namespace Kriti {
namespace Config {

boost::shared_ptr<Tree> Tree::s_singleton;

Tree::Tree() {
    m_root = boost::shared_ptr<TreeNode>(new TreeNode("root"));
}

Tree::~Tree() {
    
}

boost::weak_ptr<TreeNode> Tree::node(const std::string &path, bool create) {
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
            if(create) {
                cursor = prev.lock()->addChild(n);
            }
            else return cursor;
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

bool Tree::getBool(std::string path, bool def) {
    boost::weak_ptr<TreeNode> n = node(path, false);
    if(n.expired()) return def;
    return n.lock()->asBool();
}

int Tree::getInt(std::string path, int def) {
    boost::weak_ptr<TreeNode> n = node(path, false);
    if(n.expired()) return def;
    return n.lock()->asInt();
}

double Tree::getDouble(std::string path, double def) {
    boost::weak_ptr<TreeNode> n = node(path, false);
    if(n.expired()) return def;
    return n.lock()->asDouble();
}

std::string Tree::getString(std::string path, std::string def) {
    boost::weak_ptr<TreeNode> n = node(path, false);
    if(n.expired()) return def;
    return n.lock()->asString();
}

std::vector<std::string> Tree::childrenOf(std::string path) const {
    boost::weak_ptr<TreeNode> n = node(path);
    if(n.expired()) return std::vector<std::string>();
    
    return n.lock()->childList();
}

}  // namespace Config
}  // namespace Kriti
