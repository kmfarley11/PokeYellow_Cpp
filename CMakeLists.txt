cmake_minimum_required (VERSION 2.6)

# some cmake org
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

# versioning
set (MyProj_VERSION_MAJOR 1)
set (MyProj_VERSION_MINOR 0)
set (VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

# other project vars
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")

# add binary tree to search path for include files
include_directories ("${CMAKE_CURRENT_LIST_DIR}/source")

add_subdirectory (source)
add_subdirectory (test)


