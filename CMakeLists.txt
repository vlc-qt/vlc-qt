#############################################################################
# VLC-Qt - Qt and libvlc connector library
#############################################################################
# Copyright (C) 2008-2010 Tadej Novak
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

PROJECT(vlc-qt)
cmake_minimum_required(VERSION 2.6)

CONFIGURE_FILE(
	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

set(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
)

# Set MingW bin dir, if MingW present
IF(MINGW)
	STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR_TMP "${CMAKE_CXX_COMPILER}")
	STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR_TMP}") # Replace back slashes to slashes
ENDIF(MINGW)

# Add required libraries
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(LIBVLC REQUIRED)


###########
# Version #
###########
# libvlc-qt version number
FILE(READ VERSION VLCQT_VERSION)
STRING(REGEX REPLACE "\n" "" VLCQT_VERSION "${VLCQT_VERSION}") # get rid of the newline at the end
MESSAGE("You are compiling libvlc-qt ${VLCQT_VERSION}")

# Find Git Version Patch
FIND_PROGRAM(GIT git)
IF(GIT)
	EXECUTE_PROCESS(
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMAND ${GIT} rev-parse --short HEAD
		OUTPUT_VARIABLE GIT_OUT OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	SET(PROJECT_VERSION_PATCH "${GIT_OUT}-git")
	MESSAGE(STATUS "Git Version Patch: ${GIT_OUT}")
ELSE(GIT)
	SET(GIT_OUT 0)
ENDIF(GIT)

ADD_SUBDIRECTORY(src) 
