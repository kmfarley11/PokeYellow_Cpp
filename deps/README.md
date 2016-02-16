# DEPENDANCIES: PokeYellow_Cpp
This is where we will keep track of external libraries such as SDL, googletest, and googlemock

If you are having troubles building tests then ensure that the gtest directory is present:
 - navigate to https://github.com/google/googletest
 - download the project zip
 - extract to this folder
 - rename the extracted folder to gtest
 - in gtest/googlemock/make/Makefile ensure that the GTEST_DIR var is pointing to ../../googletest

Tools
==============
SDL
--------------
 - include and all its contents (needed)
 - lib and all contents (needed)
 - SDL2-2.0.3-MINGW (for convenience)

googletest
--------------
 - gtest/googletest and all its contents (needed)

 googlemock
--------------
 - gtest/googletest and all its contents (needed)
 - gtest/googlemock and all its contents (needed)