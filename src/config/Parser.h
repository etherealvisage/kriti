#ifndef KRITI_CONFIG__PARSER_H
#define KRITI_CONFIG__PARSER_H

#include "Tree.h"

namespace Kriti {
namespace Config {

class Parser {
private:
    boost::shared_ptr<Tree> m_tree;
public:
    Parser(boost::shared_ptr<Tree> tree);
    ~Parser() {}

    void parseFile(const std::string &filename);
};

}  // namespace Config
}  // namespace Kriti

#endif
