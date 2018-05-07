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

# after getting the paths, actually include them
include("${PROJECT_SOURCE_DIR}/FindSDL2.cmake")
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

