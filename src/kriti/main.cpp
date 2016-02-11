#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "interface/ContextRegistry.h"
#include "interface/Input.h"
#include "interface/Video.h"
#include "profile/Tracker.h"
#include "gui/Loader.h"
#include "gui/KeyboardFocus.h"
#include "render/TextureContext.h"
#include "scene/Model.h"
#include "state/DelayProxy.h"

#include "ResourceRegistry.h"
#include "XMLResource.h"
#include "AssimpWrapper.h"
#include "MessageSystem.h"

extern void gameEntryPoint();

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
    Profile::Tracker::make();

    // Create Interface objects
    Interface::Video::make();
    Interface::ContextRegistry::make();
    Interface::Input::make();

    // initialize rendering infrastructure
    Render::TextureContext::make();

    // initialize GUI system
    GUI::Loader::make();
    GUI::KeyboardFocus::make();

    // initialize the Open Asset Import Library wrapper
    AssimpWrapper::make();

    // initialize state system
    State::DelayProxy::make();

    // run application code
    gameEntryPoint();

    State::DelayProxy::destroy();

    AssimpWrapper::destroy();

    GUI::KeyboardFocus::destroy();
    GUI::Loader::destroy();

    Render::TextureContext::destroy();

    Interface::Input::destroy();
    Interface::ContextRegistry::destroy();
    Interface::Video::destroy();

    Profile::Tracker::destroy();

    ResourceRegistry::unload();

    MessageSystem::closeLogFile();

    return 0;
}
