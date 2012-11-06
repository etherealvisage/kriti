#ifndef KRITI_CONFIG__TREE_H
#define KRITI_CONFIG__TREE_H

#include <string>

#include "TreeNode.h"

namespace Kriti {
namespace Config {

class Tree {
private:
    static boost::shared_ptr<Tree> s_singleton;
public:
    static boost::shared_ptr<Tree> instance() {
        if(!s_singleton) {
            s_singleton = boost::shared_ptr<Tree>(new Tree());
        }
        return s_singleton;
    }
    static void destroy() {
        s_singleton.reset();
    }
private:
    boost::shared_ptr<TreeNode> m_root;
private:
    Tree();
public:
    ~Tree();

    boost::weak_ptr<TreeNode> node(const std::string &path, bool create = false);
    boost::weak_ptr<TreeNode> node(const std::string &path) const;

    bool getBool(std::string path, bool def = false);
    int getInt(std::string path, int def = 0);
    double getDouble(std::string path, double def = 0.0);
    std::string getString(std::string path, std::string def = "");
};

}  // namespace Config
}  // namespace Kriti

#endif
