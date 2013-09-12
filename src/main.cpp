#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "MessageSystem.h"

#include "SDL.h"

#include "ResourceRegistry.h"
#include "interface/Video.h"
#include "interface/Keyboard.h"
#include "interface/DeviceManager.h"
#include "event/EventQueue.h"
#include "event/EventRouter.h"
#include "context/ContextManager.h"
#include "game/MainMenuContext.h"
#include "profile/Tracker.h"
#include "gui/Loader.h"
#include "render/TextureContext.h"

#include "XMLResource.h"

int main() {
    using namespace Kriti;
    std::cout << "Kriti." << std::endl;


    // load configuration
    /// NOTE: here "config" uses a special hardcoded path
    auto config = ResourceRegistry::get<XMLResource>("config");

    if(!config) Message3(General, Fatal, "Could not load configuration file");
    Message3(General, Log, "Loaded configuration.");

    /* Set the log file. */
    MessageSystem::setLogFile(
        config->doc().first_element_by_path(
            "/kriti/general/logfile").text().as_string("logs/kriti-%d.log")
    );

    /* Initialize profiling infrastructure. */
    Profile::Tracker::instance();

    // explicit calls to create the singleton instances.
    boost::shared_ptr<Interface::DeviceManager> dmanager
        = Interface::DeviceManager::instance();
    Interface::Video::instance();

    // create input devices.
    dmanager->registerDevices();

    // initialize rendering infrastructure
    Render::TextureContext::instance();

    // initialize GUI system
    GUI::Loader::instance();

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

    GUI::Loader::destroy();

    Render::TextureContext::destroy();

    Interface::Video::destroy();
    Interface::DeviceManager::destroy();

    ResourceRegistry::unload();

    Profile::Tracker::destroy();

    MessageSystem::closeLogFile();

    return 0;
}
