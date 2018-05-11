##############################################
# FIND or GET SDL2 / -image
##############################################
include(FindPkgConfig)
pkg_search_module(SDL2 sdl2)
pkg_search_module(SDL2IMAGE SDL2_image>=2.0.0)

if(UNIX)

  # if linux / unix very simple... just throw error if not found (package managers make it easy)
  pkg_search_module(SDL2 REQUIRED sdl2)
  pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

elseif(WIN32 OR MSVC AND(NOT SDL2_FOUND AND NOT SDL2IMAGE_FOUND))
  
  # more robust for windows to avoid dev headaches... check then dl files if needed
  # note: this section could probably cleaned further, it will likely need to support
  # the addition of sdl mixer etc in the near future.

  # download sdl2, and sdl2image as external projs
  # note: derived from the solution found here: 
  # https://gist.github.com/SergNikitin/d8d9441120d00459201d
  set(SDL2_BASE_URL https://www.libsdl.org/)

  # Support both 32 and 64 bit builds
  if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(ARCH "/lib/x64/")
  else()
    set(ARCH "/lib/x86/")
  endif()

  # VC vs MINGW dev libs
  if(MSVC)
    set(SDL2_URL_EXT release/SDL2-devel-2.0.8-VC.zip)
    set(SDL2_IMAGE_URL_EXT projects/SDL_image/release/SDL2_image-devel-2.0.3-VC.zip)
    set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2/src/sdl2_files)
    set(SDL2IMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image/src/sdl2_image_files)
    set(INSTALL_LOC ${CMAKE_CURRENT_LIST_DIR}/bin/Debug)
    set(SDL2IMAGE_DLL_LOC ${SDL2IMAGE_DIR}${ARCH})
    set(SDL2_DLL_LOC ${SDL2_DIR}${ARCH})
  else()
    set(SDL2_URL_EXT release/SDL2-devel-2.0.8-mingw.tar.gz)
    set(SDL2_IMAGE_URL_EXT projects/SDL_image/release/SDL2_image-devel-2.0.3-mingw.tar.gz)
    set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2/src/sdl2_files/x86_64-w64-mingw32)
    set(SDL2IMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image/src/sdl2_image_files/x86_64-w64-mingw32)
    set(INSTALL_LOC ${CMAKE_CURRENT_LIST_DIR}/bin)
    set(SDL2IMAGE_DLL_LOC ${SDL2IMAGE_DIR}/bin)
    set(SDL2_DLL_LOC ${SDL2_DIR}/bin)
  endif()

  include(ExternalProject)
  if(NOT SDL2_FOUND)
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2)
      ExternalProject_Add(
        sdl2_files
        URL ${SDL2_BASE_URL}${SDL2_URL_EXT}
        PREFIX ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2
        # disable build
	CONFIGURE_COMMAND cmake -E make_directory ${INSTALL_LOC}
        BUILD_COMMAND ""
        INSTALL_COMMAND cmake -E copy_directory ${SDL2_DLL_LOC} ${INSTALL_LOC}
      )
    endif()
    set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")
    if(MSVC)
      set(SDL2_LIBRARIES "${SDL2_DLL_LOC}SDL2main.lib;${SDL2_DLL_LOC}SDL2.lib")
    else()
      # for mingw add extra sdl2 include path and different lib files (should prolly be cleaner)
      set(SDL2_INCLUDE_DIRS "${SDL2_INCLUDE_DIRS}" "${SDL2_DIR}/include/SDL2")
      set(SDL2_LIBRARIES "${SDL2_DIR}/lib/libSDL2main.a;${SDL2_DIR}/lib/libSDL2.a")
    endif()
  endif()

  if(NOT SDL2IMAGE_FOUND)
    if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image)
      ExternalProject_Add(
        sdl2_image_files
        URL ${SDL2_BASE_URL}${SDL2_IMAGE_URL_EXT}
        PREFIX ${CMAKE_CURRENT_LIST_DIR}/deps/SDL2_image
        # disable steps
	CONFIGURE_COMMAND cmake -E make_directory ${INSTALL_LOC}
        BUILD_COMMAND ""
        INSTALL_COMMAND cmake -E copy_directory ${SDL2IMAGE_DLL_LOC} ${INSTALL_LOC}
      )
    endif()
    set(SDL2IMAGE_INCLUDE_DIRS "${SDL2IMAGE_DIR}/include")
    if(MSVC)
      set(SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DLL_LOC}SDL2_image.lib")
    else()
      # for mingw add extra sdl2 include path and different lib files (should prolly be cleaner)
      set(SDL2IMAGE_INCLUDE_DIRS "${SDL2IMAGE_INCLUDE_DIRS}" "${SDL2IMAGE_DIR}/include/SDL2")
      set(SDL2IMAGE_LIBRARIES "${SDL2IMAGE_DIR}/lib/libSDL2_image.a")
    endif()
  endif()
  string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
endif(UNIX)
