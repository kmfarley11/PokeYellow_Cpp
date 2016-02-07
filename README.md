# PokeYellow_Cpp
An attempt to recreate Pokemon Yellow Version (from the ground up) via CPP, OpenGL, and SDL(2)

The current plan is to create a cross platform cpp app (using Makefile) which utilizes SDL to open up the window, and use OpenGL to do the rendering.

NOTE: since this is a project of significant scope being built (essentially) from scratch, there is a good chance that the target will be only to set up the game for the first gym's worth of content.

---> Tool Usage Plan:
SDL:
  Window creation / management
  Music integration
  Controller interface
  
OpenGL:
  Graphics rendering (expand upon this more later)
  
C++:
  Coding language for the project
  Object Oriented approach
  
googletest:
  This is not set in stone; however, it may be interesting to integrate unit testing with open gl etc

---> Approach
1.  Get Window Up and Running (check)
2.  Set Up Simple Movement W/ Relevant Sprites
3.  Get Map Loading & Room Logic to Work
4.  Set Up Music loop
4.  Set Up Database Using XML
5.     With Pokedoges
6.     With Maps / Rooms
7.  Get Player & Random Encounters Working
8.  Set Up Battle Technicalities
9.     Put moves in database
10.    Calculations for effectivity & experience etc.
11. Set Up NPCs
12.    Set up NPC convo database
13.    Get Non-Active NPCs in Pallet town to work
14.    Set up cutscene content for Pallet town
14.    Get Active NPCs in Pallet town to work
15. Hopefully by this point most low level dev will be done: from here implement up to first gym then see how it goes...

---> Cpp Expectations
Standard (clean) C++ coding practice 
  (post a link later)

 --- THE FOLLOWING ARE SUBJECT TO CHANGE --- 
Code Design (Data Abstraction) 
  main (cpp): simply opens the window, initializes the game class, and runs the loop until termination
  game (class): handles input & output via SDL and OpenGL accordingly
  player (class): controls information about the user (including the team & inventory & sprite collision)
  enemy (class): loads and controls information about current enemy trainer (including team & inventory)
  room (class): controls current map info (route X, cave X, GYM X, etc)
  npc (class): describes actions for an npc to do  which is loaded from the database, for a particular map
  
  
  
