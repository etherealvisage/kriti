#ifndef KRITI_CONFIG__TREE_NODE_H
#define KRITI_CONFIG__TREE_NODE_H

#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "MessageSystem.h"

#include "math/Vector.h"

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
        Vector,
    };
private:
    std::string m_path;

    Type m_type;
    bool m_valueBool;
    int m_valueInt;
    double m_valueDouble;
    std::string m_valueString;
    Math::Vector m_valueVector;

    std::map<std::string, boost::shared_ptr<TreeNode>> m_children;
public:
    TreeNode(std::string path);

    Type type() const { return m_type; }
    void set(bool value) { m_valueBool = value, m_type = Boolean; }
    void set(int value) { m_valueInt = value, m_type = Integer; }
    void set(double value) { m_valueDouble = value, m_type = Double; }
    void set(const std::string &value)
        { m_valueString = value, m_type = String; }
    void set(const Math::Vector &value)
        { m_valueVector = value, m_type = Vector; }

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;
    Math::Vector asVector() const;

    boost::weak_ptr<TreeNode> addChild(const std::string &name);
    boost::weak_ptr<TreeNode> child(const std::string &name) const;
    std::vector<std::string> childList() const;
};

}  // namespace Config
}  // namespace Kriti

#endif
