#include <iostream>

#include "MessageSystem.h"

#include "config/Parser.h"

int main() {
    using namespace Kriti;
    std::cout << "Kriti." << std::endl;

    boost::shared_ptr<Config::Tree> tree(new Config::Tree());

    MessageSystem::setLogFile("logs/kriti-%d.log");

    Config::Parser parser(tree);

    parser.parseFile("kriti.config");

    MessageSystem::closeLogFile();

    return 0;
}
