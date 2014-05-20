#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

CMAKE_POLICY(SET CMP0012 NEW)
IF("${CMAKE_VERSION}" VERSION_GREATER 2.8.11.1)
    CMAKE_POLICY(SET CMP0020 NEW)
ENDIF("${CMAKE_VERSION}" VERSION_GREATER 2.8.11.1)

SET(VLCQT ${PROJECT_NAME})
SET(VLCQT_WIDGETS ${PROJECT_NAME}-widgets)
SET(VLCQT_QML ${PROJECT_NAME}-qml)

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

# Detect debug build
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(LE d)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# Show all warnings
IF(NOT MSVC)
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
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
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nologo -Zc:wchar_t")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo -Zc:wchar_t -w34100 -w34189")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NOLOGO /DYNAMICBASE /NXCOMPAT")
ENDIF(MSVC)

# Support OS X 10.6 or later (64-bit only)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(CMAKE_OSX_ARCHITECTURES x86_64)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Qt
IF(FORCE_QT5)
    SET(FORCE_QT5 ${FORCE_QT5})
    SET(QT_VERSION_MAJOR 5)
ELSE(FORCE_QT5)
    SET(QT_MIN_VERSION "4.8.0")
    FIND_PACKAGE(Qt4)
ENDIF(FORCE_QT5)

IF(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)
    FIND_PACKAGE(Qt5Core REQUIRED)
    FIND_PACKAGE(Qt5Widgets REQUIRED)
    SET(QT5 1)
    MESSAGE("VLC-Qt: Build with Qt5")
ELSE(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)
    SET(QT5 0)
    MESSAGE("VLC-Qt: Build with Qt4")
ENDIF(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)

# Select modules
# Widgets
OPTION(WITH_WIDGETS "Build with Widgets" ON)
MESSAGE("VLC-Qt: Build with Widgets: ${WITH_WIDGETS}")

IF(QT5)
    # Add compiler flags for building executables (-fPIE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

    IF(Qt5_POSITION_INDEPENDENT_CODE)
        SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
    ENDIF(Qt5_POSITION_INDEPENDENT_CODE)

    # QML
    OPTION(WITH_QML "Build with QML" OFF)
    MESSAGE("VLC-Qt: Build with QML: ${WITH_QML}")
    OPTION(WITH_QML_GLES "Build QML with OpenGL ES2" OFF)
    MESSAGE("VLC-Qt: Build QML with OpenGL ES2: ${WITH_QML_GLES}")
ELSE(QT5)
    ADD_DEFINITIONS(${QT_DEFINITIONS})
    INCLUDE(${QT_USE_FILE})
ENDIF(QT5)

OPTION(STATIC "Build statically" OFF)
MESSAGE("VLC-Qt: Build statically: ${STATIC}")

# Add additional required libraries
FIND_PACKAGE(LIBVLC REQUIRED)

# Set Qt bin dir to find QtCoreX.dll and other libs to install
IF(MINGW OR MSVC)
    STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_MOC_EXECUTABLE}")
    STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes
ENDIF(MINGW OR MSVC)

# Link parameters
IF(STATIC)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml.a)
ELSEIF(MINGW)
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
ELSE(STATIC)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt.so)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets.so)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml.so)
ENDIF(STATIC)


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
ADD_SUBDIRECTORY(doc)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    ADD_SUBDIRECTORY(pkgconfig)
ELSEIF(MINGW OR MSVC)
    ADD_SUBDIRECTORY(windows)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ADD_SUBDIRECTORY(osx)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build tests" OFF)
MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

IF(${BUILD_TESTS})
    ADD_SUBDIRECTORY(tests)
ENDIF(${BUILD_TESTS})
