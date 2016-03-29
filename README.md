# PokeYellow_Cpp
An attempt to recreate Pokemon Yellow Version (from the ground up) via CPP, OpenGL, and SDL(2)

The current plan is to create a cross platform cpp app (using Makefile) which utilizes SDL backed by OpenGl to render graphics and handle IO.

NOTE: since this is a project of significant scope being built (essentially) from scratch, there is a good chance that the target will be only to set up the game for the first gym's worth of content.

Tool Usage Plan
==============
SDL2 (and SDL2_image)
--------------
 - Window creation / management
 - Music integration
 - Controller interface
 - Basic image / sprite loading
  
OpenGL
--------------
 - Low level Graphics enhancements
 - This will likely not be worked with too closely as SDL does a lot of 2D stuff
  
C++
--------------
 - Coding language for the project
 - Object Oriented approach
  
googletest
--------------
 - This is not set in stone; however, it may be interesting to integrate unit testing with open gl etc

Tiled
--------------
 - Obtain tile sets from http://www.spriters-resource.com/game_boy_gbc/pokeyell/sheet/8793/
 - Use GIMP to trim for appropriate 36 x 36 px tiles
 - Use tiled for collision tracking, tile mapping, object layering, etc.
 - Parse the tmx generated from tiled and use info however seen fit

tmxparser
--------------
 - Not being used yet, but potentially useful
 - Utilize tiled to its fullest by parsing the tmx via this 3rd party lib
 - Possibly parse home brewed later
 - To keep simple at first just use this
 - Follow installation instructions here: https://github.com/andrewrk/tmxparser

Approach
==============
Navigate to the Issues tab and select Milestones
PT-000 lays out the first *ahem* milestone for this project
 - 1:  Get Window Up and Running (check)
 - 2:  Set Up Simple Movement W/ Relevant Sprites
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

Cpp Expectations
==============
Standard (clean) C++ coding practice ...
--------------
  consider posting a link later

*THE FOLLOWING ARE SUBJECT TO CHANGE*
Code Design (Data Abstraction) 
--------------
 - main (cpp): simply opens the window, initializes the game class, and runs the loop until termination
 - game (class): handles input & output via SDL and OpenGL accordingly
 - player (class): controls information about the user (including the team & inventory & sprite collision)
 - enemy (class): loads and controls information about current enemy trainer (including team & inventory)
 - room (class): controls current map info (route X, cave X, GYM X, etc)
 - npc (class): describes actions for an npc to do  which is loaded from the database, for a particular map
  
  
  
