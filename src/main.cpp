#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "MessageSystem.h"

#include "SDL.h"

#include "config/Parser.h"
#include "ResourceRegistry.h"
#include "interface/Video.h"
#include "interface/Keyboard.h"
#include "interface/DeviceManager.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"
#include "context/ContextManager.h"
#include "game/MainMenuContext.h"
#include "render/Technique.h"

int main() {
    using namespace Kriti;
    std::cout << "Kriti." << std::endl;

    /* Create config tree. */
    boost::shared_ptr<Config::Tree> tree = Config::Tree::instance();
    Config::Parser parser(tree);

    /* Parse main configuration file. */
    parser.parseFile("kriti.config");

    /* Parse secondary configuration files. */
    parser.parseFile(tree->getString("kriti.data_path") + "techniques.config");
    parser.parseFile(tree->getString("kriti.data_path") + "gui.config");
    parser.parseFile(tree->getString("kriti.data_path") + "fonts.config");

    /* Set the log file. */
    MessageSystem::setLogFile(
        tree->getString("kriti.logfile", "logs/kriti-%d.log")
    );

    // create resource registry.
    ResourceRegistry::instance();

    // explicit calls to create the singleton instances.
    boost::shared_ptr<Interface::DeviceManager> dmanager
        = Interface::DeviceManager::instance();
    Interface::Video::instance();

    // create input devices.
    dmanager->registerDevices();

    // initialize context manager
    Context::ContextManager::instance();

    Context::ContextManager::instance()->addContext(
        new Game::MainMenuContext()
    );

    Context::ContextManager::instance()->pushContext("Game::MainMenuContext");
    
    // run the rest of the program.
    Context::ContextManager::instance()->loop();

    // clean up.
    Context::ContextManager::destroy();

    Interface::Video::destroy();
    Interface::DeviceManager::destroy();

    ResourceRegistry::destroy();

    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
