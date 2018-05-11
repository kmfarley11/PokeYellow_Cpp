##########################################
# define local recipe and executable name
##########################################
project("PokeYellow_Cpp")

file(GLOB APP_SOURCES *.cpp)

# ensure we have sdl2
include("${CMAKE_HOME_DIRECTORY}/GetSDL2.cmake")
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${APP_SOURCES})

if(MINGW)
  # need to call out related libs for mingw as it is a static lib
  set(SDL2_LIBRARIES "mingw32" ${SDL2_LIBRARIES} "imagehlp" "m" "dinput8" "dxguid" "dxerr8" "user32" "gdi32" "winmm" "imm32" "ole32" "oleaut32" "shell32" "version" "uuid")
endif()

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

# if we had to dl / extract sdl2 libs ensure that is done before compilation
if(NOT SDL2_FOUND)
  add_dependencies(${PROJECT_NAME} sdl2_files)
endif()
if(NOT SDL2IMAGE_FOUND)
  add_dependencies(${PROJECT_NAME} sdl2_image_files)
endif()

