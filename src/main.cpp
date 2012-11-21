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

    parser.parseFile(tree->getString("kriti.data_path") + "techniques.config");

    /* Set the log file. */
    MessageSystem::setLogFile(
        tree->getString("kriti.logfile", "logs/kriti-%d.log")
    );

    // create resource registry.
    ResourceRegistry::instance();

    Math::Vector v = tree->getVector("example.vector");
    Message("Vector parsing: " << v.x() << "," << v.y() << "," << v.z());

    // explicit calls to create the singleton instances.
    boost::shared_ptr<Interface::DeviceManager> dmanager
        = Interface::DeviceManager::instance();
    Interface::Video::instance();

    // create input devices.
    dmanager->registerDevices();

    // initialize context manager
    Context::ContextManager::instance();

    boost::shared_ptr<Render::Technique> simpleTechnique
        = ResourceRegistry::instance()->get<Render::Technique>("simple");

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
