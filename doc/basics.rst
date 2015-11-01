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
        PairPrinter(int private) : m_private(private) {}

        void print(int n) { Message("Pair: (" << private << "," << n << ")"); }
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

TODO: elaborate
