#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

# Show all warnings
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -W")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -W")

SET(CMAKE_VERBOSE_MAKEFILE ON)

# Qt5 support
OPTION(WITH_QT5 "Build with Qt5" OFF)
MESSAGE("\nVLC-Qt: Build with Qt5: ${WITH_QT5}\n")

IF(WITH_QT5)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

    # Qt5 dirs
    INCLUDE(Qt5)
    QT5_FIND_LIBRARY_DIR(QT_LIBRARY_DIR)

    SET(Qt5Core_DIR "${QT_LIBRARY_DIR}/cmake/Qt5Core")
    SET(Qt5Gui_DIR "${QT_LIBRARY_DIR}/cmake/Qt5Gui")
    SET(Qt5Widgets_DIR "${QT_LIBRARY_DIR}/cmake/Qt5Widgets")
ENDIF(WITH_QT5)

# Search for Qt and other libraries
IF(WITH_QT5)
    SET(QT_MIN_VERSION "5.0.0")
    ADD_DEFINITIONS(-DQt5)
ELSE(WITH_QT5)
    SET(QT_MIN_VERSION "4.6.0")
    ADD_DEFINITIONS(-DQt4)
ENDIF(WITH_QT5)

# Qt
IF(WITH_QT5)
    FIND_PACKAGE(Qt5Core REQUIRED)
    FIND_PACKAGE(Qt5Gui REQUIRED)
    FIND_PACKAGE(Qt5Widgets REQUIRED)
ELSE(WITH_QT5)
    FIND_PACKAGE(Qt4 REQUIRED)
ENDIF(WITH_QT5)

# Add additional required libraries
FIND_PACKAGE(LIBVLC REQUIRED)

# Set Qt bin dir to find QtCoreX.dll and other libs to install
IF(MINGW)
    STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_QMAKE_EXECUTABLE}")
    STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes
ENDIF(MINGW)

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
MESSAGE("\nVLC-Qt: You are compiling libvlc-qt ${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}.${VLCQT_VERSION_BUGFIX}\n")

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
ADD_SUBDIRECTORY(pkgconfig)
ADD_SUBDIRECTORY(doc)
IF(MINGW)
    ADD_SUBDIRECTORY(windows)
ENDIF(MINGW)


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build tests" OFF)
MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

IF(${BUILD_TESTS})
    ADD_SUBDIRECTORY(test)
ENDIF(${BUILD_TESTS})
