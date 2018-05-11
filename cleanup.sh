#!/bin/bash

# USAGE: sh cleanup.sh
# it essentially finds and removes all various artifacts which may be leftover from cmake / make / vs
# this was made since cmake doesn't have an implicit cmake clean option
rm -rf CMakeCache.txt CMakeFiles/ source/CMakeFiles/ test/CMakeFiles/ && rm -rf Win32/ .vs/ PokeYellow_Cpp.sln *.vcxproj* deps/SDL2* *.sln *.pc ./bin/* Makefile source/Makefile test/Makefile deps/gtest */Debug */Release */Win32 */*vcxproj* */*.dir */cmake_install.cmake */*.sln */*.o */*.tcl
