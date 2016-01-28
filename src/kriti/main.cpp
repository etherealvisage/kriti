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
#include "Globals.h"

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
    GlobalHelper<Profile::Tracker>::make();

    // Create Interface objects
    GlobalHelper<Interface::Video>::make();
    GlobalHelper<Interface::ContextRegistry>::make();
    GlobalHelper<Interface::Input>::make();

    // initialize rendering infrastructure
    GlobalHelper<Render::TextureContext>::make();

    // initialize GUI system
    GlobalHelper<GUI::Loader>::make();
    GlobalHelper<GUI::KeyboardFocus>::make();

    // initialize the Open Asset Import Library wrapper
    GlobalHelper<AssimpWrapper>::make();

    // initialize state system
    GlobalHelper<State::DelayProxy>::make();

    // run application code
    gameEntryPoint();

    GlobalHelper<State::DelayProxy>::destroy();

    GlobalHelper<GUI::KeyboardFocus>::destroy();
    GlobalHelper<GUI::Loader>::destroy();

    GlobalHelper<Render::TextureContext>::destroy();

    GlobalHelper<Interface::Input>::destroy();
    GlobalHelper<Interface::ContextRegistry>::destroy();
    GlobalHelper<Interface::Video>::destroy();

    ResourceRegistry::unload();

    GlobalHelper<Profile::Tracker>::destroy();

    MessageSystem::closeLogFile();

    return 0;
}
