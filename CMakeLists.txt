cmake_minimum_required(VERSION 2.6)
project(libSPRITE)

# Version Number.
set(libSPRITE_MAJOR_VERSION 1)
set(libSPRITE_MINOR_VERSION 1)
set(libSPRITE_PATCH_VERSION 1)
set(libSPRITE_VERSION ${libSPRITE_MAJOR_VERSION}.${libSPRITE_MINOR_VERSION}.${libSPRITE_PATCH_VERSION})

# Set compilation options.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wparentheses -Wuninitialized -Wcomment -Wformat")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wparentheses -Wuninitialized -Wcomment -Wformat -Weffc++")
add_definitions(-DXPRINT_LOCATION)

# Add the list of directories to search.
include_directories("${PROJECT_SOURCE_DIR}")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message("CMake build type is ${CMAKE_BUILD_TYPE}")

# Add unit test build type
set(CMAKE_CXX_FLAGS_TEST "-DASSERT_THROWS_EXCEPTION" CACHE STRING "Extra flags used for building unit tests")
mark_as_advanced(CMAKE_CXX_FLAGS_TEST)
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Test." FORCE)

# Add the subdirectories.
add_subdirectory(base)
add_subdirectory(units)
add_subdirectory(net)
add_subdirectory(math)
add_subdirectory(util)
add_subdirectory(SRTX)
add_subdirectory(SCALE)

# Install support for find_package(libSPRITE)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/libSPRITE/libsprite-config-version.cmake"
    VERSION ${libSPRITE_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_file(cmake/libsprite-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/libSPRITE/libsprite-config.cmake"
    @ONLY)

set(ConfigPackageLocation lib/cmake/libSPRITE)
install(FILES
    cmake/libsprite-config.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/libSPRITE/libsprite-config-version.cmake"
    DESTINATION ${ConfigPackageLocation}
    COMPONENT Devel)

# Build a CPack driven installer package.
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/license.pdf")
set (CPACK_PACKAGE_VERSION_MAJOR "${libSPRITE_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${libSPRITE_VERSION_MINOR}")
include (CPack)

# Uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
