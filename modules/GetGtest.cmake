##############################################
# Download and compile gtest
##############################################
# download gtest and include as external static proj
# note: derived / copied from the solution found here: 
# https://github.com/kaizouman/gtest-cmake-example
find_package(Threads REQUIRED)
include(ExternalProject)
ExternalProject_Add(
	gtest
	URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
	PREFIX ${CMAKE_HOME_DIRECTORY}/deps/gtest
	# disable install step
	INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)

# include libgtest
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
if(UNIX OR MINGW)
set_target_properties(libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
elseif(MSVC)
set_target_properties(libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gtestd.lib"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif()

# now for libgmock properties
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)
if(UNIX OR MINGW)
set_target_properties(libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
elseif(MSVC)
set_target_properties(libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/lib/Debug/gmockd.lib"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
endif()

# provide header includes from test libs
include_directories(
	"${source_dir}/googletest/include"
	"${source_dir}/googlemock/include"
)

