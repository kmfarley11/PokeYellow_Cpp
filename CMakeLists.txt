cmake_minimum_required (VERSION 2.6)
project ("PokeYellow_Cpp")

# some cmake org?...
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# versioning
set (MyProj_VERSION_MAJOR 1)
set (MyProj_VERSION_MINOR 0)
set (VERSION ${MyProj_VERSION_MAJOR}.${MyProj_VERSION_MINOR})

# other project vars
set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# configure header for Cmake settings
#configure_file (
#	"${PROJECT_SOURCE_DIR}/src/MyProjConfig.h.in"
#	"${PROJECT_BINARY_DIR}/include/MyProjConfig.h"
#)

# add binary tree to search path for include files
include_directories ("${PROJECT_SOURCE_DIR}/source")
#include_directories ("${PROJECT_SOURCE_DIR}/source" "${PROJECT_SOURCE_DIR}/deps/include")
#link_directories ("${PROJECT_SOURCE_DIR}/deps/lib")

add_subdirectory(source)
add_subdirectory(test)
