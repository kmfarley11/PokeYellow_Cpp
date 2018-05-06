##########################################
# define local recipe and executable name
##########################################
set (APP_SOURCES
	tester.cpp
	GameTester.cpp ${PROJECT_SOURCE_DIR}/source/Game.cpp
	GameObjectTester.cpp ${PROJECT_SOURCE_DIR}/source/GameObject.cpp
	PlayerTester.cpp ${PROJECT_SOURCE_DIR}/source/Player.cpp
	RoomTester.cpp	${PROJECT_SOURCE_DIR}/source/Room.cpp
)

set (APPLICATION_NAME tester)
add_executable (${APPLICATION_NAME} ${APP_SOURCES})

##########################################
# INCLUDES (sdl2/image + gtest + gmock)...
##########################################

# include / force sdl2 / sdl2-image
include (FindPkgConfig)
pkg_search_module (SDL2 REQUIRED sdl2)
pkg_search_module (SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries (${APPLICATION_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# download gtest and include as external static proj
find_package(Threads REQUIRED)
include (ExternalProject)
ExternalProject_Add (
	gtest
	URL https://github.com/google/googletest/archive/master.zip
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
	# disable install step
	INSTALL_COMMAND ""
)
ExternalProject_Get_Property (gtest source_dir binary_dir)

# include libgtest
add_library (libgtest IMPORTED STATIC GLOBAL)
add_dependencies (libgtest gtest)
set_target_properties (libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# now for libgmock properties
add_library (libgmock IMPORTED STATIC GLOBAL)
add_dependencies (libgmock gtest)
set_target_properties (libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# provide header includes from test libs
include_directories (
	"${source_dir}/googletest/include"
	"${source_dir}/googlemock/include"
)

# finally, link the test libs
target_link_libraries (${APPLICATION_NAME} 
	${CMAKE_THREAD_LIBS_INIT}
	libgtest
	libgmock
)

