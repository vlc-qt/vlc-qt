#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

PROJECT(vlc-qt)
CMAKE_POLICY(SET CMP0012 NEW)

IF(WITH_QT5)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
ELSE(WITH_QT5)
    CMAKE_MINIMUM_REQUIRED(VERSION 2.8.6)
ENDIF(WITH_QT5)

SET(VLCQT_SHARED ${PROJECT_NAME})
SET(VLCQT_WIDGETS_SHARED ${PROJECT_NAME}-widgets)
SET(VLCQT_QML_SHARED ${PROJECT_NAME}-qml)

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

# Automatically run moc, if required
SET(CMAKE_AUTOMOC ON)
# Verbose makefile
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Show all warnings
IF(NOT MSVC)
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
ENDIF(NOT MSVC)

# Make final release build smaller
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

# Statically link with libgcc
IF(MINGW)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
ENDIF(MINGW)

IF(MSVC)
   ADD_DEFINITIONS("/W3 /D_CRT_SECURE_NO_WARNINGS /wd4005 /wd4996 /nologo")
ENDIF(MSVC)

# Select modules
# Widgets
OPTION(WITH_WIDGETS "Build with Widgets" ON)
MESSAGE("VLC-Qt: Build with Widgets: ${WITH_WIDGETS}")
# QML
OPTION(WITH_QML "Build with QML" OFF)
MESSAGE("VLC-Qt: Build with QML: ${WITH_QML}")

# Qt5 support
OPTION(WITH_QT5 "Build with Qt5" OFF)
MESSAGE("VLC-Qt: Build with Qt5: ${WITH_QT5}")

IF(WITH_QT5)
    # Qt5 dirs
    INCLUDE(Qt5)
    QT5_FIND_LIBRARY_DIR(QT_LIBRARY_DIR)

    SET(Qt5Core_DIR "${QT_LIBRARY_DIR}/cmake/Qt5Core")
    SET(Qt5Widgets_DIR "${QT_LIBRARY_DIR}/cmake/Qt5Widgets")

    SET(WITH_QML OFF)
ENDIF(WITH_QT5)

# Search for Qt and other libraries
IF(WITH_QT5)
    SET(QT_MIN_VERSION "5.0.0")
    ADD_DEFINITIONS(-DQt5)
ELSE(WITH_QT5)
    SET(QT_MIN_VERSION "4.8.0")
    ADD_DEFINITIONS(-DQt4)
ENDIF(WITH_QT5)

# Qt
IF(WITH_QT5)
    FIND_PACKAGE(Qt5Core REQUIRED)
    FIND_PACKAGE(Qt5Widgets REQUIRED)

#   Add compiler flags for building executables (-fPIE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

    IF(Qt5_POSITION_INDEPENDENT_CODE)
        SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
    ENDIF(Qt5_POSITION_INDEPENDENT_CODE)
ELSE(WITH_QT5)
    FIND_PACKAGE(Qt4 REQUIRED)

    IF(WITH_QML)
        SET(QT_USE_QTDECLARATIVE True)
    ENDIF(WITH_QML)

    ADD_DEFINITIONS(${QT_DEFINITIONS})
    INCLUDE(${QT_USE_FILE})
ENDIF(WITH_QT5)

# Add additional required libraries
FIND_PACKAGE(LIBVLC REQUIRED)

# Set Qt bin dir to find QtCoreX.dll and other libs to install
IF(MINGW OR MSVC)
    STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_QMAKE_EXECUTABLE}")
    STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes
ENDIF(MINGW OR MSVC)

# Link parameters
IF(MINGW)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt.dll.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets.dll.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml.dll.a)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt.dylib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets.dylib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml.dylib)
ELSEIF(MSVC)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/vlc-qt.lib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/vlc-qt-widgets.lib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/vlc-qt-qml.lib)
ELSE(MINGW)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt.so)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets.so)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml.so)
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
    IF(NOT GIT_OUT STREQUAL "")
        SET(PROJECT_VERSION_PATCH "${GIT_OUT}-git")
        MESSAGE(STATUS "Git Version Patch: ${GIT_OUT}")
    ENDIF(NOT GIT_OUT STREQUAL "")
ELSEIF(GITBUILD)
    SET(PROJECT_VERSION_PATCH "${GITBUILD}-git")
ELSE(GIT)
    SET(GIT_OUT 0)
ENDIF(GIT)


###################
# Compile and set #
###################
ADD_SUBDIRECTORY(src) 
ADD_SUBDIRECTORY(pkgconfig)
ADD_SUBDIRECTORY(doc)
IF(MINGW OR MSVC)
    ADD_SUBDIRECTORY(windows)
ENDIF(MINGW OR MSVC)


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build tests" OFF)
MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

IF(${BUILD_TESTS})
    ADD_SUBDIRECTORY(tests)
ENDIF(${BUILD_TESTS})
