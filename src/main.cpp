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

    // create a keyboard device.
    dmanager->registerDevice<Interface::Keyboard>();

    // temporary loop
    bool quit = false;
    while(!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) quit = true;
            else dmanager->handleEvent(&event);
        }
        dmanager->pollDevices();
        SDL_Delay(30);
    }

    /* clean up. */
    Interface::Video::destroy();
    Interface::DeviceManager::destroy();

    MessageSystem::closeLogFile();

    Config::Tree::destroy();

    return 0;
}
