##############################################
# FIND SDL2 / -image (if windows find in deps)
##############################################
if (UNIX)

  # if linux / unix very simple... just find it
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
  pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

elseif (WIN32 OR MSVC)

  # if windows, expect dev to extract to deps folder and remove version from name
  set(SDL2_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/SDL2")
  set(SDL2IMAGE_DIR "${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image")

  set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
  set(SDL2IMAGE_INCLUDE_DIRS "${SDL2IMAGE_DIR}/include")

  # Support both 32 and 64 bit builds
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
    set(SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}/lib/x64/SDL2_image.lib")
  else ()
    set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x86/SDL2.lib;${SDL2_DIR}/lib/x86/SDL2main.lib")
    set(SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}/lib/x86/SDL2_image.lib")
  endif ()

  string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

endif (UNIX)
