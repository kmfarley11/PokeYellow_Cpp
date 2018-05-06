##########################################
# define local recipe and executable name
##########################################
set (APP_SOURCES
	main.cpp
	Game.cpp
	GameObject.cpp
	Player.cpp
	Room.cpp
)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

##########################################
# INCLUDES (sdl2/image)
##########################################
include (FindPkgConfig)
pkg_search_module (SDL2 REQUIRED sdl2)
pkg_search_module (SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

