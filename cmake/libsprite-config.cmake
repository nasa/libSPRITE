# -config file for libSPRITE for use my find_package(libSPRITE)
#
# Defines the following macros
# libSPRITE_INCLUDE_DIRS - Path to header files.
# libSPRITE_LINK_DIRS - Path to libraries
# libSPRITE_LIBRARIES - Libraries supplied by libSPRITE.

set(libSPRITE_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include/SPRITE")
set(libSPRITE_LINK_DIRS "${CMAKE_INSTALL_PREFIX}/lib/SPRITE")
set(libSPRITE_LIBRARIES SPRITE_SCALE SPRITE_SRTX SPRITE_util SPRITE_math SPRITE_net SPRITE_units)
