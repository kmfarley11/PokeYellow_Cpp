##########################################
# define local recipe and executable name
##########################################
project ("PokeYellow_Cpp")

file (GLOB APP_SOURCES *.cpp)

# after getting the paths, actually include them
include("${CMAKE_HOME_DIRECTORY}/FindSDL2.cmake")
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${APP_SOURCES})

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

