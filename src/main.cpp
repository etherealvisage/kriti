#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "MessageSystem.h"

#include "SDL.h"

#include "config/Parser.h"
#include "interface/Video.h"
#include "interface/Keyboard.h"
#include "interface/DeviceManager.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"
#include "context/ContextManager.h"
#include "game/MainMenuContext.h"

void setQuit(bool *quit, bool down) {
    if(down == false) *quit = true;
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
    MessageSystem::setLogFile(
        tree->getString("kriti.logfile", "logs/kriti-%d.log")
    );

    // explicit calls to create the singleton instances.
    Interface::DeviceManager *dmanager = Interface::DeviceManager::instance();
    Interface::Video::instance();

    // create input devices.
    dmanager->registerDevices();

    // initialize context manager
    Context::ContextManager::instance();

    Context::ContextManager::instance()->addContext(
        new Game::MainMenuContext()
    );

    Context::ContextManager::instance()->pushContext("main menu");
    
    // run the rest of the program.
    Context::ContextManager::instance()->loop();

    // clean up.
    Context::ContextManager::destroy();

    Interface::Video::destroy();
    Interface::DeviceManager::destroy();

    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
