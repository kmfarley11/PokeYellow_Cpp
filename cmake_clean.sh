#!/bin/bash

# USAGE: sh cmake_clean.sh (or alias in bashrc for global availability)
# it essentially finds and removes all cmake files in the current / sub dir
# but it ignores CMakeLists and this script
find . -maxdepth 2 -iname "*make*" | grep -v "CMakeList" | grep -v "cmake_clean" | xargs rm -rf
