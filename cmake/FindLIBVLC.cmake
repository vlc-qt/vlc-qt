#############################################################################
# VLC - CMake module
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
# Original author: Rohit Yadav <rohityadav89@gmail.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# If it's found it sets LIBVLC_FOUND to TRUE
# and following variables are set:
#  LIBVLC_INCLUDE_DIR
#  LIBVLC_LIBRARY


# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing.

#Put here path to custom location
#example: /home/user/vlc/include etc..
FIND_PATH(LIBVLC_INCLUDE_DIR vlc/vlc.h
    "$ENV{LIBVLC_INCLUDE_PATH}"
    "$ENV{LIB_DIR}/include"
    "$ENV{LIB_DIR}/include/vlc"
    "/usr/include"
    "/usr/include/vlc"
    "/usr/local/include"
    "/usr/local/include/vlc"
    #mingw
    c:/msys/local/include
    NO_DEFAULT_PATH
)
FIND_PATH(LIBVLC_INCLUDE_DIR vlc.h)

#Put here path to custom location
#example: /home/user/vlc/lib etc..
FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc PATHS
    "$ENV{LIBVLC_LIBRARY_PATH}"
    "$ENV{LIB_DIR}/lib"
    #mingw
    c:/msys/local/lib
    NO_DEFAULT_PATH
)

#Put here path to custom location
#example: /home/user/vlc/lib etc..
FIND_LIBRARY(LIBVLC_CORE_LIBRARY NAMES vlccore libvlccore PATHS
    "$ENV{LIBVLC_LIBRARY_PATH}"
    "$ENV{LIB_DIR}/lib"
    #mingw
    c:/msys/local/lib
    NO_DEFAULT_PATH
)

FIND_LIBRARY(LIBVLC_LIBRARY NAMES vlc libvlc)

IF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLC_CORE_LIBRARY)
    SET(LIBVLC_FOUND TRUE)
ENDIF (LIBVLC_INCLUDE_DIR AND LIBVLC_LIBRARY AND LIBVLC_CORE_LIBRARY)

IF (LIBVLC_FOUND)
    IF (NOT LIBVLC_FIND_QUIETLY)
        MESSAGE(STATUS "Found LibVLC include-dir path: ${LIBVLC_INCLUDE_DIR}")
        MESSAGE(STATUS "Found LibVLC library path: ${LIBVLC_LIBRARY}")
        MESSAGE(STATUS "Found LibVLC core library path: ${LIBVLC_CORE_LIBRARY}")
    ENDIF (NOT LIBVLC_FIND_QUIETLY)
ELSE (LIBVLC_FOUND)
    IF (LIBVLC_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find LibVLC")
    ENDIF (LIBVLC_FIND_REQUIRED)
ENDIF (LIBVLC_FOUND)
