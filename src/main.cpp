#include <iostream>

#include "MessageSystem.h"

#include "config/Parser.h"
#include "interface/Video.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"

void listener(int param) {
    std::cout << "Listener! Param: " << param << std::endl;
}

void invoker(boost::signal<void ()> *signal) {
    (*signal)();
}

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
    er.exampleListener.connect(listener);

    eq.enqueue(er.exampleListener, 42);

    eq.process();

    Interface::Video::destroy();

    /* Close the log file as part of cleanup. */
    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
