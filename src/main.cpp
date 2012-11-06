#include <iostream>

#include "MessageSystem.h"

#include "config/Parser.h"
#include "interface/Video.h"

int main() {
    using namespace Kriti;
    std::cout << "Kriti." << std::endl;

    /* Create config tree. */
    boost::shared_ptr<Config::Tree> tree = Config::Tree::instance();
    Config::Parser parser(tree);

    /* Parse main configuration file. */
    parser.parseFile("kriti.config");

    /* Set the log file. */
    MessageSystem::setLogFile(tree->getString("kriti.logfile", "logs/kriti-%d.log"));

    Interface::Video::instance();

    

    Interface::Video::destroy();

    /* Close the log file as part of cleanup. */
    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
