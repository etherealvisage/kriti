Kriti basics
============

.. highlight:: c++

Let's look at a simple example. As was discussed in the
`Buildsystem <architecture.html#buildsystem>`_ section earlier, we only need to
consider one source file that exports the ``gameEntryPoint`` function. So, for
us, a skeleton example might be something like::

    void gameEntryPoint() {

    }

Obviously, this isn't very interesting. So, let's start looking at some of the
basic parts of the Kriti architecture.

Message and logging system
--------------------------

Let's start by taking a look at how the logging system works. Debugging
information is very important, and while much of the time a ``std::cout`` does
the trick, sometimes we want a more high-powered solution. Kriti's
``MessageSystem`` is intended to address that need. In particular, it:

 * Allows multiple levels of verbosity on a per-module basis,
 * Prepends timestamp to message,
 * Automatically logs written content to a file.

Using it is very simple::

    #include "kriti/MessageSystem.h"

    void gameEntryPoint() {
        Message("This is a generic log message.");
        Message2(Debug, "This is a generic debugging message.");
        Message2(Error, "This is a generic error message.");
        Message3(Game, Debug, "This is a game debugging message.");
    }

These will be formatted as::

    [17:28:56 General      Log    ]         This is a generic log message.
    [17:28:56 General      Debug  ]         This is a generic debugging message.
    [17:28:56 General      Error  ]         This is a generic error message.
    [17:28:56 Game         Debug  ]         This is a game debugging message.

TODO: elaborate how to create custom categories.

Context and state system
------------------------

One of the most critical parts of kriti to manage is the state and context
system. The idea is sort of to refactor the main event loop of a game into
smaller, more easily-managed pieces.

There are three important classes that are involved here: ``State::Context``,
``State::Context::Event``, and ``State::Context::Listener``. Each
``State::Context`` acts as a single event loop, which can optionally proxy
events to another context if it proves to be useful. We'll start explaining how
this all works with a simple code example::

    #include "kriti/state/Context.h"
    #include "kriti/MessageSystem.h"

    using namespace Kriti;

    void listener1() {
        Message("listener1()");
    }

    void listener2() {
        Message("listener2()");
    }

    void gameEntryPoint() {
        auto context = boost::make_shared<State::Context>();

        context->addListener("event1", listener1);
        context->addListener("event1", listener2);
        context->addListener("event2", listener2);

        context->fire("event1");
        context->fire("event2");

        context->processQueued();
    }

This was intended to be fairly self-explanatory for people who have seen event
systems before, but let's walk through it quickly:

 * Contexts can have named events (such as ``event1``) and have C-style
   functions registered as callbacks for when they are fired,
 * Events can be fired by name,
 * Nothing happens until the queue is processed.

Of course, this is somewhat boring. What if we want to pass around events by
something other than an ugly string? We can do that; that's what ``getEvent``
does --- it returns a ``State::Context::Event`` instance, which can then be
fired off by itself if you so choose::

    #include "kriti/state/Context.h"
    #include "kriti/MessageSystem.h"

    using namespace Kriti;

    void listener1() {
        Message("listener1()");
    }

    void gameEntryPoint() {
        auto context = boost::make_shared<State::Context>();

        context->addListener("event1", listener1);

        context->getEvent("event1")->fire(boost::tuple<>());

        context->processQueued();
    }

This got a little different in the middle there --- in particular, it
introduces the concept that events can have parameters, which are passed around
as ``boost::tuple`` instances. However, in this case, our listener function
doesn't take any parameters, so we just instantiate it to be an empty tuple.

This lets us fire events in arbitrary contexts, sure. But what if we want
something other than a C-style global or static function to be the callback?
Well, we can do this, because ``addListener`` actually takes a
``boost::function``. So anything that has an ``operator()`` can be used,
including lambdas or member functions. A simple example, this time including
parameters::

    #include "kriti/state/Context.h"
    #include "kriti/MessageSystem.h"

    using namespace Kriti;

    class PairPrinter {
    private:
        int m_private;
    public:
        PairPrinter(int priv) : m_private(priv) {}

        void print(int n) {
            Message("Pair: (" << m_private << "," << n << ")");
        }
    };

    void gameEntryPoint() {
        auto context = boost::make_shared<State::Context>();
        auto event = context->addEvent<int>();

        context->addListener(event, boost::function<void (int)>(
            boost::bind(&PairPrinter::print, new PairPrinter(3), _1)));
        context->addListener(event, boost::function<void (int)>(
            boost::bind(&PairPrinter::print, new PairPrinter(4), _1)));
        context->addListener(event, boost::function<void (int)>(
            [](int v){ Message("lambda value: " << v); }));

        event->fire(boost::make_tuple(2));

        context->processQueued();
    }

Finally, the ``addListener`` function returns an instance of
``State::Context::Listener``, which has a ``disconnect()`` function to allow
you to stop listening for events.

Resource system
---------------

Kriti has a resource system that is designed to hide the actual source of the
data being loaded. The intention is to allow for files to be loaded from the
standard filesystem, from a tarball/zip file, from the network, etc. This
generality does make it slightly more complicated to use than a simple
``fstream`` or ``FILE *``, but it also allows for resources to automatically be
shared where appropriate and have parsers etc. applied to file contents.

There are two main classes to consider in the resource system. First is the
base class of all loadable resources, ``Resource``. This is essentially an
empty base class, with its only function ``loadFrom(std::string id)``, where
``id`` is a string to denote what to load from. This function is only relevant
if you are implementing your own type of resource.

The second class is the ``ResourceRegistry`` class. This is a singleton class
that stores references to loaded ``Resource`` instances. It provides a simple
template accessor method that makes this straightforwards to use.

Let's show how this all works by using a simple example resource type,
``FileResource``. This simply loads a file's content into memory and then
allows it to be accessed through standard C++ data types::

    #include "kriti/FileResource.h"
    #include "kriti/ResourceRegistry.h"

    void gameEntryPoint() {
        auto file = Kriti::ResourceRegistry::get<Kriti::FileResource>("file.txt");

        if(!file) {
            Message3(Game, Fatal, "Couldn't open required file!");
        }

        Message3(Game, Debug, "File content: " << file->fileContent());
    }

The class ``Kriti::FileResource`` will load files from the data path specified
in the XML configuration file, which we'll get to in a bit. If not specified,
this is by default the path ``data/``.

Once loaded once by the ResourceRegistry, the resource will be kept in memory
until explicitly removed with the ``ResourceRegistry::clear`` function. Note
that descriptors are kept in separate namespaces per resource type, so
``ResourceRegistry::get<FileResource>("name")`` will return a different result
than ``ResourceRegistry::get<Render::Texture>("name")``. To avoid confusion
with this, you should avoid having resource types that are castable to each
other.

Let's say, for the moment, that we want to add a new resource type,
``NPCResource``. This needs some XML configuration information, a texture, and
maybe some lines of dialogue. We can do this by creating a new subclass of
``Resource`` and specifying a ``loadFrom`` function, like so::

    #include "kriti/FileResource.h"
    #include "kriti/XMLResource.h"
    #include "kriti/render/Texture.h"
    #include "kriti/ResourceRegistry.h"

    class NPCResource : public Kriti::Resource {
    private:
        boost::shared_ptr<Kriti::XMLResource> m_config;
        boost::shared_ptr<Kriti::Render::Texture> m_appearance;
        boost::shared_ptr<Kriti::FileResource> m_dialogueFile;
        std::map<std::string, int> m_dialogueMap;
    public:
        // should return true if the resource was loaded successfully, false otherwise
        virtual bool loadFrom(std::string identifier) {
            m_config = Kriti::ResourceRegistry::get<Kriti::XMLResource>(
                "npcs/" + identifier);
            if(!m_config) return false;

            m_dialogueFile = Kriti::ResourceRegistry::get<Kriti::FileResource>(
                "npcs/" + identifier);
            if(!m_dialogueFile) return false;

            m_appearance = Kriti::ResourceRegistry::get<Kriti::Render::Texture>(
                "npc_" + identifier);
            if(!m_appearance) return false;

            // construct mapping of dialogue names to lines in the dialogue file from config in XML file

            return true;
        }

        std::string getDialogueLine(std::string which) {
            return m_dialogueFile.fileLines()[m_dialogueMap[which]];
        }
    };

As a rule of thumb, if you have any functions in a resource that involve
expensive computation, you should probably cache the result. The intended
design pattern is that ``Resource`` instances may be accessed from various
locations in the codebase, including hot-paths.

Configuration
-------------

.. highlight:: xml

As was mentioned earlier in the resource system section, there is a
'configuration' resource. This is an XML file, usually called ``kriti.xml``,
placed in the same directory as the executable. This is accessed by the special
``XMLResource`` name "config". This stores information such as the directory to
put log files in, where to load further data files, etc. A configuration file
with all the default values present would be as follows::

    <kriti>
        <general>
            <data-path>data/</data-path>
            <logfile>logs/kriti-%d.log</logfile>
            <profile>false</profile>
        </general>
        <video>
            <resolution width="800" height="600" bpp="0" fullscreen="false" />
            <msaa enabled="false" samples="4" />
        </video>
    </kriti>

.. highlight:: c++
