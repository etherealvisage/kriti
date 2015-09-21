#if 1
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind/protect.hpp>

#include "interface/ContextRegistry.h"
#include "interface/Input.h"
#include "interface/Video.h"
#include "profile/Tracker.h"
#include "gui/Loader.h"
#include "render/TextureContext.h"
#include "scene/Model.h"

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
    Profile::Tracker::instance();

    // explicit calls to create the singleton instances.
    Interface::Video::instance();
    Interface::ContextRegistry::instance();
    Interface::Input::instance();

    // initialize rendering infrastructure
    Render::TextureContext::instance();

    // initialize GUI system
    GUI::Loader::instance();

    // initialize the Open Asset Import Library wrapper
    AssimpWrapper::instance();

    // run application code
    gameEntryPoint();

    GUI::Loader::destroy();

    Render::TextureContext::destroy();

    Interface::Input::destroy();
    Interface::ContextRegistry::destroy();
    Interface::Video::destroy();

    ResourceRegistry::unload();

    Profile::Tracker::destroy();

    MessageSystem::closeLogFile();

    return 0;
}
#else

#include <iostream>

#include "state/Context.h"

void test(int x) {
    std::cout << "x: " << x << std::endl;
}

void anon(int x) {
    std::cout << "(anon) x: " << x << std::endl;
}

int main() {
    Kriti::State::Context con;

    auto orig = con.addListener("test", boost::function<void (int)>(test));

    con.fire("test", boost::make_tuple(42));

    auto repeat = con.addListener("test", &con, "test");

    con.processQueued();

    auto anon_event = con.addEvent<int>();
    auto anon_listener = con.addListener(anon_event,
        boost::function<void (int)>(test));

    con.fire(anon_event, boost::make_tuple(21));

    con.processQueued();

    return 0;
}
#endif
