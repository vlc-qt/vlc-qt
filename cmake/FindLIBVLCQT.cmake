#############################################################################
# CMake module to search for VLC-Qt (Qt and libvlc connector library)
#############################################################################
# Authors: Rohit Yadav <rohityadav89@gmail.com>
#          Tadej Novak <ntadej@users.sourceforge.net>
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# This file may be used under the terms of the
# GNU General Public License version 3.0 as published by the
# Free Software Foundation and appearing in the file LICENSE.GPL
# included in the packaging of this file.
#############################################################################
#
# If it's found it sets LIBVLCQT_FOUND to TRUE
# and following variables are set:
#  LIBVLCQT_INCLUDE_DIR
#  LIBVLCQT_LIBRARY


# FIND_PATH and FIND_LIBRARY normally search standard locations
# before the specified paths. To search non-standard paths first,
# FIND_* is invoked first with specified paths and NO_DEFAULT_PATH
# and then again with no specified paths to search the default
# locations. When an earlier FIND_* succeeds, subsequent FIND_*s
# searching for the same item do nothing.

#Put here path to custom location
#example: /home/user/vlc-qt/include etc..
FIND_PATH(LIBVLCQT_INCLUDE_DIR vlc-qt/Instance.h
	"$ENV{LIBVLCQT_INCLUDE_PATH}"
	"$ENV{LIB_DIR}/include"
	"$ENV{LIB_DIR}/include/vlc-qt"
	"/usr/include"
	"/usr/include/vlc-qt"
	"/usr/local/include"
	"/usr/local/include/vlc-qt"
	c:/msys/local/include
	NO_DEFAULT_PATH
)
FIND_PATH(LIBVLCQT_INCLUDE_DIR Instance.h)

#Put here path to custom location
#example: /home/user/vlc/lib etc..
FIND_LIBRARY(LIBVLCQT_LIBRARY NAMES vlc-qt PATHS
	"$ENV{LIBVLCQT_LIBRARY_PATH}"
	"$ENV{LIB_DIR}/lib"
	c:/msys/local/lib
	NO_DEFAULT_PATH
)
FIND_LIBRARY(LIBVLCQT_LIBRARY NAMES vlc-qt)

IF (LIBVLCQT_INCLUDE_DIR AND LIBVLCQT_LIBRARY)
	SET(LIBVLCQT_FOUND TRUE)
ENDIF (LIBVLCQT_INCLUDE_DIR AND LIBVLCQT_LIBRARY)

IF (LIBVLCQT_FOUND)
	IF (NOT LIBVLCQT_FIND_QUIETLY)
		MESSAGE(STATUS "Found libvlc-qt include-dir path: ${LIBVLCQT_INCLUDE_DIR}")
		MESSAGE(STATUS "Found libvlc-qt library path: ${LIBVLCQT_LIBRARY}")
	ENDIF (NOT LIBVLCQT_FIND_QUIETLY)
ELSE (LIBVLCQT_FOUND)
	IF (LIBVLCQT_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find libvlc-qt")
	ENDIF (LIBVLCQT_FIND_REQUIRED)
ENDIF (LIBVLCQT_FOUND)

