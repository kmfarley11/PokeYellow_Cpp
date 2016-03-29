# SOURCE: PokeYellow_Cpp
An attempt to recreate Pokemon Yellow Version (from the ground up) via CPP, OpenGL, and SDL(2 + _image)

The files will be briefly described below (information is currently tentative).

See the license directory for more info and a copy of the open source license.

*THE FOLLOWING ARE SUBJECT TO CHANGE*
Code Design (Data Abstraction) 
--------------
 - main (cpp): simply opens the window, initializes the game class, and runs the loop until termination
 - game (class): handles input & output via SDL and OpenGL accordingly
 - player (class): will control information about the user (including the team & inventory & sprite collision)
 - enemy (class): will load and control information about current enemy trainer (including team & inventory)
 - room (class): will control current map info (route X, cave X, GYM X, etc)
 - npc (class): will describe actions for an npc to do  which is loaded from the database, for a particular map
  
  
  
