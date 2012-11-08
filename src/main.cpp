#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "MessageSystem.h"

#include "config/Parser.h"
#include "interface/Video.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"

void listener(int param) {
    std::cout << "Listener! Param: " << param << std::endl;
}

class ListenerClass {
public:
    void listener(int param) { std::cout << "param: " << param << std::endl; }
};

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

    Event::EventQueue eq;

    Event::EventRouter er;
    ListenerClass lc;
    er.exampleListener.connect(boost::bind(&ListenerClass::listener, &lc, _1));

    eq.enqueue(er.exampleListener, 2);

    // 42 should be printed before 2 . . .
    er.fire(er.exampleListener, 42);

    eq.process();

    Interface::Video::destroy();

    /* Close the log file as part of cleanup. */
    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
