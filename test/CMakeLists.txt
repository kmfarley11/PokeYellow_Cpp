##########################################
# define local recipe and executable name
##########################################

project("tester")
file(GLOB TEST_SOURCES *.cpp)
file(GLOB APP_SOURCES ${CMAKE_HOME_DIRECTORY}/source/*.cpp)
list(REMOVE_ITEM APP_SOURCES ${CMAKE_HOME_DIRECTORY}/source/main.cpp)

# ensure we have sdl2
include("${CMAKE_MODULE_PATH}/GetSDL2.cmake")
if(MINGW)
  # need to call out related libs for mingw as it is a static lib
  set(SDL2_LIBRARIES "mingw32" ${SDL2_LIBRARIES} "imagehlp" "m" "dinput8" "dxguid" "dxerr8" "user32" "gdi32" "winmm" "imm32" "ole32" "oleaut32" "shell32" "version" "uuid")
endif()
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# ensure we have gtest
include("${CMAKE_MODULE_PATH}/GetGtest.cmake")
enable_testing()

add_executable(${PROJECT_NAME} ${APP_SOURCES} ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} 
	${CMAKE_THREAD_LIBS_INIT}
	libgtest
	libgmock
)

# if we had to dl / extract sdl2 libs ensure that is done before compilation
if(NOT SDL2_FOUND)
  add_dependencies(${PROJECT_NAME} sdl2_files)
endif()
if(NOT SDL2IMAGE_FOUND)
  add_dependencies(${PROJECT_NAME} sdl2_image_files)
endif()

##########################################
# COVERAGE (integrate gcov)
##########################################
if(UNIX)
  include(CodeCoverage)
  append_coverage_compiler_flags()

  set(COVERAGE_EXCLUDES
      ${PROJECT_SOURCE_DIR}/deps/*
      /usr/include/*
      /**/googletest/*
      /**/googlemock/*)
  setup_target_for_coverage_lcov(NAME coverage EXECUTABLE ${PROJECT_NAME})
endif()

##########################################
# UNIT TESTS (integrate ctest & gtest)
##########################################
include(CTest)
add_test(NAME all_tests COMMAND ${PROJECT_NAME} WORKING_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")
target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCES="${CMAKE_RESOURCES_DIRECTORY}/")
