#include <fstream>
#include <cctype>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include "Parser.h"
#include "MessageSystem.h"

namespace Kriti {
namespace Config {

Parser::Parser(boost::shared_ptr<Tree> tree) : m_tree(tree) {
    
}

void Parser::parseFile(const std::string &filename) {
    std::ifstream file(filename);

    if(!file.good()) {
        Message3(Config, Error, "Cannot open config file " << filename);

        return;
    }

    std::string line;
    int lineNumber = 0;
    while(std::getline(file, line)) {
        lineNumber ++;
        // Strip whitespace.
        unsigned i;

        for(i = 0; i < line.size() && std::isspace(line[i]); i ++) ;
        line = line.substr(i);

        // if blank or comment, skip the line.
        if(line.size() == 0 || line[0] == '#') continue;

        std::string::size_type ei = line.find("=");
        if(ei == std::string::npos || ei == 0) {
            Message3(Config, Warning, "Malformed config file on line #" << lineNumber);
        }

        std::string path = line.substr(0, ei);

        // Strip whitespace.
        for(i = path.size()-1; std::isspace(path[i]); i --) ;
        path = line.substr(0, i+1);

        std::string value = line.substr(ei+1);

        // Strip whitespace.
        for(i = 0; i < value.size() && std::isspace(value[i]); i ++) ;
        value = value.substr(i);
        for(i = value.size()-1; std::isspace(value[i]); i --) ;
        value = value.substr(0, i+1);

        // get node, allowing creation
        boost::weak_ptr<TreeNode> node = m_tree->node(path, true);
        
        // use a stringstream to parse.
        std::istringstream ssv(value);

        int iv;
        double dv;
        std::string sv;
        if(ssv >> iv) {
            node.lock()->set(iv);
        }
        else if(ssv >> dv) {
            node.lock()->set(dv);
        }
        else if(value == "true" || value == "false") {
            node.lock()->set(value == "true");
        }
        else {
            if(value[0] != '"' || value[value.length()-1] != '"') {
                Message3(Config, Warning, "Don't know how to parse value \""
                    << value << "\" on line #" << lineNumber);
            }
            else {
                node.lock()->set(value.substr(1, value.length()-2));
            }
        }
    }

    file.close();
}

}  // namespace Config
}  // namespace Kriti
