##########################################
# CMAKE TOP (versioning etc.)
##########################################
cmake_minimum_required(VERSION 3.1.3)

# some cmake org
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/modules)

# versioning
set(MyProj_VERSION_MAJOR 1)
set(MyProj_VERSION_MINOR 0)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR})

# other project vars
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib")
set(CMAKE_RESOURCES_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/resources")

# ctest and gtest integration
option(test "Build tests." ON)

# add binary tree to search path for include files
include_directories("${CMAKE_CURRENT_LIST_DIR}/source")

# for MSVC make all code use proper (multi-threaded) runtime libs for gtest to work
# found here: https://github.com/xmfbit/gtest-VisualStudio-CMake-example/blob/master/CMakeLists.txt
if(MSVC)
  set(variables 
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
	CMAKE_CXX_FLAGS_RELWITHDEBINFO
	CMAKE_CXX_FLAGS_MINSIZEREL
  )
  foreach(variable ${variables})
	if(${variable} MATCHES "/MD")
	  string(REGEX REPLACE "/MD" "/MT" ${variable} "${${variable}}")
	endif()
  endforeach()
endif()

# add sdl2 to main solution if necessary (msvc only)
include("${CMAKE_MODULE_PATH}/GetSDL2.cmake")

add_subdirectory(source)
add_subdirectory(test)

set(CMAKE_DEFAULT_STARTUP_PROJECT PokeYellow_Cpp)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "PokeYellow_Cpp")

