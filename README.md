Pixel Dust Game Engine (PDG)
============================

PDG is an open source, professional quality 2D game engine. It provides 
system independent abstractions of common elements needed by game developers. 
It can be used directly from C++ or used from scripting languages like 
Javascript.

This is the documentation for the Javascript API.

Features
--------
- integrated with Node.js
- high performance Javascript via Google's V8 engine
- event driven
- cross platform
- 2D OpenGL hardware accelerated graphics
- resource and file management
- user input handling
- timers
- networking
- sound
- animation including jQuery-like easing functions
- sprites
- tile based maps
- physics support using Chipmunk Physics
- works with node inspector for Javascript debugging
- interactive Javascript console mode

Documentation
-------------

Documentation (HTML and Man pages) are included in the docs directory, and can also be found online (along with comment areas) at:

http://ezavada.com/pdg/javascript/html/

Design Goals
------------

PDG is focused on making a broad array of capabilities available to developers 
regardless of the OS platform they are targeting. Currently it works on Mac OS X, 
Windows, and iOS.

The PDG API is designed to make simple things easy to do, without adding undue 
complexity to more complicated problems.

History
-------

PDG was originally developed in 2003 by Ed Zavada of Pixel Dust Games for use in Catan Online. It was later updated by Dream Rock Studios for use in their game
Parthenon. Those updates included OpenGL hardware acceleration, a sprite engine, and iOS support. In 2012 it was further updated with Chipmunk physics, Javascript
bindings, and then made open source under the MIT license.

Usage assumptions
-----------------

PDG is supplied in several different forms:
- an ANSI C++ SDK
- a Javascript SDK that includes a binary runtime for Mac OS X and Windows
- an npm package for Node.js for server side programming

No languages other than Javascript and C++ are currently supported, though Ruby bindings have been created in the past. The Javascript bindings could serve as a guide for anyone wishing to add support for other languages.

Roles and Responsibilities
--------------------------

PDG is integrated with Node.js, so all of the excellent networking, file i/o, encyption, process management and debugging facilities of Node.js are available to you. For multiplayer games you can write your server with Node.js, and use PDG as an add-on module if needed. On the client side, you can run as a double clickable application with PDG providing most of the functionality, and Node.js modules available for networking and so forth.

In most cases PDG does not duplicate functionality already in Node.js. There are, however a few notable exceptions:

- **Timers**: PDG provides its own TimerManager, which greatly improves on the functionality available through standard Javascript/Node.js.  
- **Events**: PDG has its own event system, and does not relay events through Node.js's EventEmitter. That would be easy to add at an application level if desired.
- **Logging**: PDG has a LogManager that writes time-stamped log entries with runtime configurable logging levels.

What's missing?
---------------

There are a few things we'd like to add to PDG, but haven't had time to build yet. Some
are pretty simple, others rather larger. In no particular order, they are:

- Pure Javascript HTML5 implementation so you can run your game in a browser
- Port.drawRadialGradient()
- Example Code
- Unit Tests for every part of PDG
- FluidLayer for simulating floating objects
- OuterSpaceLayer for simulating gravitational attraction between objects
- Android port
- Support for graphics on Linux
- Support for rotation of TileLayers
- DiagonalTileLayer for Ultima Online style isometric maps
- HexGridTileLayer for board games

Game Kits
---------

PDG doesn't provide any implementation of higher level functionality commonly used in 
games, such as AI, pathfinding, dialog trees, tooltips, character classes, dynamic map 
generation, segmented loading of large maps, etc.. You should be able to build those 
things as needed for your game.

We do plan to build Game Kits for a variety of game genres on top of PDG, so check to
see if they are available and have what you need.
