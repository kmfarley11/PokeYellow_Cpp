#!/bin/bash

# DEPRECATED: only necessary if you run `cmake .` from the repo root...
#   you should be running `cmake ..` from the build folder!

# USAGE: sh cleanup.sh
# note 1: if on windows, running the above in git-bash or WSL will get the job done. 
# note 2: all files cleaned up here are gitignored anyways, its just for if you wanna nuke your build (deps and all)
# note 3: if this is desired to be more robust for more project types then this can definitely be cleaned up
# it essentially finds and removes all various artifacts which may be leftover from cmake / make / vs
# this was made since cmake doesn't have an implicit cmake clean option
rm -rf CMakeCache.txt CMakeFiles/ source/CMakeFiles/ test/CMakeFiles/ && \
    rm -rf Win32/ .vs/ PokeYellow_Cpp.sln *.vcxproj* deps/SDL2* *.sln *.pc \
        ./bin/* Makefile source/Makefile test/Makefile deps/gtest */Debug \
        */Release */Win32 */*vcxproj* */*.dir */cmake_install.cmake */*.sln \
        */*.o */*.tcl cmake_install.cmake Debug Testing */Testing *.tcl \
        */CTestTestfile* CTestTestfile* *-project *-workspace */*-project \
        */*-workspace */*.a */.vs */CMakeCache.txt *.cbp */*.cbp *.layout \
        */*.layout */*.project */*.cproject *.project *.cproject .metadata \
        */.metadata RemoteSystemsTempFiles
