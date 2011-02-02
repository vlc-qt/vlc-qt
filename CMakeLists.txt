#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	IF(GITBUILD)
		SET(GIT_OUT GITBUILD)
	ELSE(GITBUILD)
		SET(GIT_OUT 0)
	ENDIF(GITBUILD)
ENDIF(GIT)


##########
# Source #
##########
ADD_SUBDIRECTORY(src) 


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build Tests" OFF)
MESSAGE("Build Tests: ${BUILD_TESTS}")

IF(${BUILD_TESTS})
	ADD_SUBDIRECTORY(test)
ENDIF(${BUILD_TESTS})
