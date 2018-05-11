##########################################
# define local recipe and executable name
##########################################
project ("tester")
file (GLOB TEST_SOURCES *.cpp)
file (GLOB APP_SOURCES ${CMAKE_HOME_DIRECTORY}/source/*.cpp)
list (REMOVE_ITEM APP_SOURCES ${CMAKE_HOME_DIRECTORY}/source/main.cpp)

##########################################
# EXTRA INCLUDES (sdl2 / -image + gtest + gmock)...
##########################################
# after getting the paths, actually include them
include("${CMAKE_HOME_DIRECTORY}/GetSDL2.cmake")
if (MINGW OR WIN32)
  # need to call out related libs for mingw as it is a static lib
  set (SDL2_LIBRARIES "mingw32" ${SDL2_LIBRARIES} "imagehlp" "m" "dinput8" "dxguid" "dxerr8" "user32" "gdi32" "winmm" "imm32" "ole32" "oleaut32" "shell32" "version" "uuid")
endif ()
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# download gtest and include as external static proj
# note: derived / copied from the solution found here: 
# https://github.com/kaizouman/gtest-cmake-example
find_package(Threads REQUIRED)
include (ExternalProject)
ExternalProject_Add (
	gtest
	URL https://github.com/google/googletest/archive/master.zip
	PREFIX ${CMAKE_HOME_DIRECTORY}/deps/gtest
	# disable install step
	INSTALL_COMMAND ""
)
ExternalProject_Get_Property (gtest source_dir binary_dir)

# include libgtest
add_library (libgtest IMPORTED STATIC GLOBAL)
add_dependencies (libgtest gtest)
if (UNIX OR MINGW)
set_target_properties (libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
elseif (MSVC)
set_target_properties (libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/Debug/gtestd.lib"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif ()

# now for libgmock properties
add_library (libgmock IMPORTED STATIC GLOBAL)
add_dependencies (libgmock gtest)
if (UNIX OR MINGW)
set_target_properties (libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
elseif (MSVC)
set_target_properties (libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/Debug/gmockd.lib"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif ()

# provide header includes from test libs
include_directories (
	"${source_dir}/googletest/include"
	"${source_dir}/googlemock/include"
)

add_executable (${PROJECT_NAME} ${APP_SOURCES} ${TEST_SOURCES})

# finally, link the test libs
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries (${PROJECT_NAME} 
	${CMAKE_THREAD_LIBS_INIT}
	libgtest
	libgmock
)

