# PokeYellow_Cpp
An attempt to recreate Pokemon Yellow Version (from the ground up) via CPP, and SDL(2)

The current plan is to create a cross platform cpp app (using Makefile) which utilizes SDL backed by OpenGl to render graphics and handle IO.

NOTE: since this is a project of significant scope being built (essentially) from scratch, there is a good chance that the target will be only to set up the game for the first gym's worth of content.

This information is currently for developers only, no stable release yet

Installation / Usage
==============
 - obtain [cmake](https://cmake.org/download/)
 - clone or download the source code from here
 - (linux only) install the development packages for sdl2, sdl2_image, and pthreads via apt or yum etc.
    - i.e. `sudo apt install build-essential cmake make libsdl2-dev libsdl2-image-dev libpthread-stubs0-dev`)
 - cd into the root of PokeYellow_Cpp and run `cmake -S . -B ./build` (see the tool details for examples)
 - build the source (i.e. `make -C ./build`)
    - binaries will be placed in ./bin
 - run `./bin/PokeYellow_Cpp` for the game, `./bin/tester` for the unit tests
    - unit tests can also be run via ctest from the test directory
 - dev environment notes
    - Visual Studio (Windows-Only) users:
       - `cmake . -G "Visual Studio 15 2017" -B ./build`
       - open up Project.sln at the root of the repo and build the whole solution
       - to run, right click on PokeYellow_Cpp and debug instance
          - note: Release isn't implicitly supported right now, you will have to copy the dlls into that folder
       - for unit testing: Test > Run > All Tests
    - Visual Studio Code (Linux-Only) users:
       - the .vscode/ folder is already included in the repo, but tasks are designed only for Linux w/ Makefile usage
       - suggested extensions include: C/C++, C/C++ Clang Command Adapter
       - to debug: Tasks > Run Task... > config debug, Tasks > Run Task... > build, then F5
    - note: Unix makefiles, mingw makefiles, and Visual Studio 2017 were the only ports tested
       - if you desire a different IDE or setup and find it doesn't work, you are welcome to open issues or modify the cmake files
 - note some work has been done to stand up a docker image and do some automation via python
    - checkout `python3 support/proj.py --help` for more details
    - i.e. `python3 support/proj.py --native --clean --config --build --test`
    - the docker side doesn't support gui yet so some tests will fail if run without `--native`

Tool Details
==============

CMake
--------------
 - install / build management
 - to ease cross platform support
    - MSVC-Project-style : `cmake . -G "Visual Studio 15 2017" -B ./build`
    - UNIX-Makefile-style : `cmake . -B ./build`
    - MINGW-Makefile-style : `cmake . -G "MinGW Makefiles" -B ./build`
 - package cmake for linux
 - https://cmake.org/download/ for either linux or windows

SDL2 (and SDL2_image)
--------------
 - Note: currently considering replacing with glew, glut etc. for graphics see Issue #13
 - Window creation / management
 - Music integration
 - Controller interface
 - Basic image / sprite loading
 - If Linux install both (cmake will download for you if using mingw or msvc):
    - [SDL2](https://www.libsdl.org/download-2.0.php#source) : package libsdl2-dev/SDL2-devel for linux
    - [SDL2_Image](https://www.libsdl.org/projects/SDL_image/) : package libsdl2-image-dev/SDL2_image-devel for linux

OpenGL
--------------
 - Low level Graphics enhancements
 - This will likely not be worked with too closely as SDL does a lot of 2D stuff
 - *Once the main functionality is provided, OpenGl may replace SDL to mitigate third party dependancies*
  
C++
--------------
 - Coding language for the project
 - Object Oriented approach
 - See expectations below
  
googletest (and googlemock)
--------------
 - Unit testing for object verification / validation
 - Once the core is mostly developed, unit tests should be included with any push to master
 - Unit tests will be run before merging any pull request and must pass

Tiled
--------------
 - Obtain tile sets from http://www.spriters-resource.com/game_boy_gbc/pokeyell/sheet/8793/
 - Use GIMP to trim for appropriate 16 x 16 px tiles
 - Use tiled for collision tracking, tile mapping, object layering, etc.
 - Parse the tmx generated from tiled and use info however seen fit

tmxparser
--------------
 - Not set in stone; however, this would make tmx data easier to handle
 - Not in use yet
 - The con would be yet another 3rd party dependancy which may add overhead
 - Follow installation instructions here: https://github.com/andrewrk/tmxparser

Cpp / Git Expectations
==============
Standard (clean) C++ coding practice ...
--------------
 - code should be readable
    - this means that the intent of the code should be obvious, if not then comment
    - coding style should also be consistent with what is already in place...
       - i.e. "{" on their own line etc.
 - unit tests should be maintained and enhanced
    - this will not be strongly enforced until most classes (core dev) has already been done)
       - no need to lock code down until a definitive structure is in place
    - pull requests will only be merged if all unit tests pass (just run tester exe after building)
 - no project (nor object) files should be pushed into the repo (other than CMakeLists.txt and .cmake files)
    - one exception being .vscode as the files within are relatively pathed, and lightweight

*THE FOLLOWING ARE SUBJECT TO CHANGE*
Code Design (Data Abstraction) 
--------------
 - main (cpp): simply opens the window, initializes the game class, and runs the loop until termination
 - Game (class): handles input & output via SDL and OpenGL accordingly
 - Player (class): controls information about the user (including the team & inventory & sprite collision)
 - Enemy (class): loads and controls information about current enemy trainer (including team & inventory)
 - Room (class): controls current map info (route X, cave X, GYM X, etc)
 - Npc (class): describes actions for an npc to do  which is loaded from the database, for a particular map
  
Approach
==============
Navigate to the Issues tab and select Milestones
PT-000 lays out the first *ahem* milestone for this project
 - ~~1:  Get Window Up and Running (check)~~
 - ~~2:  Set Up Simple Movement W/ Relevant Sprites (check)~~
 - 3:  Get Map Loading & Room Logic to Work
 - 4:  Set Up Music loop
 - 5:  Set Up Database Using XML
 - 6:     With Pokedoges
 - 7:     With Maps / Rooms
 - 8:  Get Player & Random Encounters Working
 - 9:  Set Up Battle Technicalities
 - 10:    Put moves in database
 - 11:    Calculations for effectivity & experience etc.
 - 12: Set Up NPCs
 - 13:    Set up NPC convo database
 - 14:    Get Non-Active NPCs in Pallet town to work
 - 15:    Set up cutscene content for Pallet town
 - 16:    Get Active NPCs in Pallet town to work
 - 17: Hopefully by this point most low level dev will be done: from here implement up to first gym then see how it goes... 
