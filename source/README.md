# SOURCE: PokeYellow_Cpp
An attempt to recreate Pokemon Yellow Version (from the ground up) via CPP, OpenGL, and SDL(2 + _image)

The files will be briefly described below (information is currently tentative).

See the root directory for more info and the licensing directory for a copy of the open source license.

*THE FOLLOWING ARE SUBJECT TO CHANGE*
Code Design (Data Abstraction) 
--------------
 - main (cpp): simply opens the window, initializes the game class, and runs the loop until termination
 - Game (class): handles input & output via SDL and OpenGL accordingly
 - Player (class): will control information about the user (including the team & inventory & sprite collision)
 - Enemy (class): will load and control information about current enemy trainer (including team & inventory)
 - Room (class): will control current map info (route X, cave X, GYM X, etc)
 - Npc (class): will describe actions for an npc to do  which is loaded from the database, for a particular map  
