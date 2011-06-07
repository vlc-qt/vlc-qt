#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2011 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################

PROJECT(vlc-qt)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0012 NEW)

SET(VLCQT_SHARED ${PROJECT_NAME})

CONFIGURE_FILE(
	"${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
	"${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

SET(CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/cmake
)

INCLUDE(ManageString)

# Set MingW bin dir, if MingW present
IF(MINGW)
	STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR_TMP "${CMAKE_CXX_COMPILER}")
	STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR_TMP}") # Replace back slashes to slashes
ENDIF(MINGW)

# Add required libraries
FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(LIBVLC REQUIRED)

# Set Qt4 bin dir to find QtCore4.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_QMAKE_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes

###########
# Version #
###########
# libvlc-qt version number
FILE(READ VERSION VLCQT_VERSION)
STRING(REGEX REPLACE "\n" "" VLCQT_VERSION "${VLCQT_VERSION}") # get rid of the newline at the end
STRING_SPLIT(VLCQT_VERSION_LIST "." ${VLCQT_VERSION})
LIST(GET VLCQT_VERSION_LIST 0 VLCQT_VERSION_MAJOR)
LIST(GET VLCQT_VERSION_LIST 1 VLCQT_VERSION_MINOR)
LIST(GET VLCQT_VERSION_LIST 2 VLCQT_VERSION_BUGFIX)
MESSAGE("You are compiling libvlc-qt ${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}.${VLCQT_VERSION_BUGFIX}")

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
		SET(PROJECT_VERSION_PATCH "${GITBUILD}-git")
	ELSE(GITBUILD)
		SET(GIT_OUT 0)
	ENDIF(GITBUILD)
ENDIF(GIT)


###################
# Compile and set #
###################
ADD_SUBDIRECTORY(src) 

# Windows
IF(MINGW)
	STRING(REGEX REPLACE "\\\\" "/" LIBVLC_INCLUDE_DIR "${LIBVLC_INCLUDE_DIR}")

	STRING(REGEX REPLACE "sdk/include" "" LIBVLC_BIN_DIR "${LIBVLC_INCLUDE_DIR}")
	STRING(REGEX REPLACE "include" "bin" LIBVLC_BIN_DIR "${LIBVLC_BIN_DIR}")

	SET(Qt_Libs
		${QT_BIN_DIR}/libgcc_s_dw2-1.dll
		${QT_BIN_DIR}/mingwm10.dll
		${QT_BIN_DIR}/QtCore4.dll
		${QT_BIN_DIR}/QtGui4.dll
	)
	SET(Vlc_Libs
		${LIBVLC_BIN_DIR}/libvlc.dll
		${LIBVLC_BIN_DIR}/libvlccore.dll
	)
	FILE(GLOB Vlc_Plugins ${LIBVLC_BIN_DIR}/plugins/*.dll)
ENDIF(MINGW)


################
# Installation #
################
# Windows Extra
IF(MINGW)
	INSTALL(FILES ${Qt_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
	INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
	INSTALL(FILES ${Vlc_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/plugins")
ENDIF(MINGW)


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build Tests" OFF)
MESSAGE("Build Tests: ${BUILD_TESTS}")

IF(${BUILD_TESTS})
	ADD_SUBDIRECTORY(test)
ENDIF(${BUILD_TESTS})
