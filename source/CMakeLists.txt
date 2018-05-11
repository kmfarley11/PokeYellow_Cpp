##########################################
# define local recipe and executable name
##########################################
project ("PokeYellow_Cpp")

file (GLOB APP_SOURCES *.cpp)

# after getting the paths, actually include them
include("${CMAKE_HOME_DIRECTORY}/GetSDL2.cmake")
include_directories (${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${APP_SOURCES})

if (MINGW OR WIN32)
  # need to call out related libs for mingw as it is a static lib
  set (SDL2_LIBRARIES "mingw32" ${SDL2_LIBRARIES} "imagehlp" "m" "dinput8" "dxguid" "dxerr8" "user32" "gdi32" "winmm" "imm32" "ole32" "oleaut32" "shell32" "version" "uuid")
endif ()

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

