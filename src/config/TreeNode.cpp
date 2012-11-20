#include "TreeNode.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Config {

TreeNode::TreeNode(std::string path) : m_path(path), m_type(Container) {
}

bool TreeNode::asBool() const {
    if(m_type != Boolean) {
        Message3(Config, Warning, m_path << ": this is not a boolean node!");
        return false;
    }

    return m_valueBool;
}

int TreeNode::asInt() const {
    if(m_type != Integer) {
        Message3(Config, Warning, m_path << ": this is not an integer node!");
        return -1;
    }

    return m_valueInt;
}

double TreeNode::asDouble() const {
    // Provide automatic up-casting from int -> double.
    if(m_type == Integer) {
        return m_valueInt;
    }
    else if(m_type == Double) {
        return m_valueDouble;
    }
    else {
        Message3(Config, Warning, m_path << ": this is not a double node!");
        return -1.0;
    }
}

std::string TreeNode::asString() const {
    if(m_type != String) {
        Message3(Config, Warning, m_path << ": this is not a string node!");
        Message3(Config, Warning, m_path << ": actual type is " << m_type);
        return "";
    }
    return m_valueString;
}

boost::weak_ptr<TreeNode> TreeNode::addChild(const std::string &name) {
    m_children[name] = boost::shared_ptr<TreeNode>(
        new TreeNode(m_path + "." + name)
    );
    return m_children[name];
}

boost::weak_ptr<TreeNode> TreeNode::child(const std::string &name) const {
    auto i = m_children.find(name);
    if(i == m_children.end()) {
        return boost::weak_ptr<TreeNode>();
    }
    return i->second;
}

std::vector<std::string> TreeNode::childList() const {
    std::vector<std::string> list;
    for(auto i : m_children) {
        list.push_back(i.first);
    }
    return list;
}

}  // namespace Config
}  // namespace Kriti
