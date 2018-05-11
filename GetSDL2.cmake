##############################################
# FIND SDL2 / -image (if windows find in deps)
##############################################
if (UNIX)

  # if linux / unix very simple... just find it or throw error
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
  pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

elseif (WIN32 OR MSVC)
  
  # make more robust for windows to avoid dev headaches... check then dl if needed
  include(FindPkgConfig)
  pkg_search_module(SDL2 sdl2)
  pkg_search_module(SDL2IMAGE SDL2_image>=2.0.0)

  # if not found, use manual pathing
  # download sdl2, and sdl2image as external projs
  # note: derived / copied from the solution found here: 
  # https://gist.github.com/SergNikitin/d8d9441120d00459201d
  set (SDL2_BASE_URL https://www.libsdl.org/)

  # VC vs MINGW dev libs
  if (MSVC)
    set (SDL2_URL_EXT release/SDL2-devel-2.0.8-VC.zip)
    set (SDL2_IMAGE_URL_EXT projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip)
    set (SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2/src/sdl2_files)
    set (SDL2IMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image/src/sdl2_image_files)
    set (INSTALL_LOC ${CMAKE_CURRENT_LIST_DIR}/bin/Debug)
  else ()
    set (SDL2_URL_EXT release/SDL2-devel-2.0.8-mingw.tar.gz)
    set (SDL2_IMAGE_URL_EXT projects/SDL_image/release/SDL2_image-devel-2.0.3-mingw.tar.gz)
    set (SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2/src/sdl2_files/x86_64-w64-mingw32)
    set (SDL2IMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image/src/sdl2_image_files/x86_64-w64-mingw32)
    set (INSTALL_LOC ${CMAKE_CURRENT_LIST_DIR}/bin)
  endif ()
  
  # Support both 32 and 64 bit builds
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(ARCH "/lib/x64/")
  else ()
    set(ARCH "/lib/x86/")
  endif ()

  include (ExternalProject)
  if (NOT SDL2_FOUND)
    if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2)
      ExternalProject_Add (
        sdl2_files
        URL ${SDL2_BASE_URL}${SDL2_URL_EXT}
        PREFIX ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2
        # disable build
	CONFIGURE_COMMAND cmake -E make_directory ${INSTALL_LOC}
        BUILD_COMMAND ""
        INSTALL_COMMAND cmake -E copy_directory ${SDL2_DIR}/bin ${INSTALL_LOC}
      )
    endif()
    set (SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
    if (MSVC)
      set (SDL2_LIBRARIES "${SDL2_DIR}${ARCH}SDL2main.lib;${SDL2_DIR}${ARCH}SDL2.lib")
    else ()
      # for mingw add extra sdl2 include path and different lib files (should prolly be cleaner)
      set (SDL2_INCLUDE_DIRS "${SDL2_INCLUDE_DIRS}" "${SDL2_DIR}/include/SDL2")
      set (SDL2_LIBRARIES "${SDL2_DIR}/lib/libSDL2main.a;${SDL2_DIR}/lib/libSDL2.a")
    endif ()
  endif ()

  if (NOT SDL2IMAGE_FOUND)
    if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image)
      ExternalProject_Add (
        sdl2_image_files
        URL ${SDL2_BASE_URL}${SDL2_IMAGE_URL_EXT}
        PREFIX ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image
        # disable steps
	CONFIGURE_COMMAND cmake -E make_directory ${INSTALL_LOC}
        BUILD_COMMAND ""
        INSTALL_COMMAND cmake -E copy_directory ${SDL2IMAGE_DIR}/bin ${INSTALL_LOC}
      )
    endif ()
    set (SDL2IMAGE_INCLUDE_DIRS "${SDL2IMAGE_DIR}/include")
    if (MSVC)
      set (SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}${ARCH}SDL2_image.lib")
    else ()
      # for mingw add extra sdl2 include path and different lib files (should prolly be cleaner)
      set (SDL2IMAGE_INCLUDE_DIRS "${SDL2IMAGE_INCLUDE_DIRS}" "${SDL2IMAGE_DIR}/include/SDL2")
      set (SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}/lib/libSDL2_image.a")
    endif ()
  endif ()
  string (STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif (UNIX)
