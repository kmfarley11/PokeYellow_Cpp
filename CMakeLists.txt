cmake_minimum_required (VERSION 2.6)
project ("PokeYellow_Cpp")

# some cmake org
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# versioning
set (MyProj_VERSION_MAJOR 1)
set (MyProj_VERSION_MINOR 0)
set (VERSION ${MyProj_VERSION_MAJOR}.${MyProj_VERSION_MINOR})

# other project vars
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# add binary tree to search path for include files
include_directories ("${PROJECT_SOURCE_DIR}/source")

add_subdirectory (source)
add_subdirectory (test)


