#ifndef KRITI_CONFIG__TREE_NODE_H
#define KRITI_CONFIG__TREE_NODE_H

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "MessageSystem.h"

namespace Kriti {
namespace Config {

class TreeNode {
public:
    enum Type {
        Container,
        Boolean,
        Integer,
        Double,
        String,
    };
private:
    std::string m_path;

    Type m_type;
    bool m_valueBool;
    int m_valueInt;
    double m_valueDouble;
    std::string m_valueString;

    std::map<std::string, boost::shared_ptr<TreeNode>> m_children;
public:
    TreeNode(std::string path);

    void set(bool value) { m_valueBool = value, m_type = Boolean; }
    void set(int value) { m_valueInt = value, m_type = Integer; }
    void set(double value) { m_valueDouble = value, m_type = Double; }
    void set(const std::string &value)
        { m_valueString = value, m_type = String; }

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;

    boost::weak_ptr<TreeNode> addChild(const std::string &name);
    boost::weak_ptr<TreeNode> child(const std::string &name) const;
};

}  // namespace Config
}  // namespace Kriti

#endif
