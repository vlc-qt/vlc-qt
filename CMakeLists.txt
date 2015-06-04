#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)
CMAKE_POLICY(VERSION 3.0.2)

SET(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/config
)

INCLUDE(ParseVersion)

PROJECT(vlc-qt
        VERSION ${VLCQT_VERSION})

SET(VLCQT ${PROJECT_NAME})
SET(VLCQT_WIDGETS ${PROJECT_NAME}-widgets)
SET(VLCQT_QML ${PROJECT_NAME}-qml)
SET(VLCQT_TEST VLC-Qt)

INCLUDE(CustomTargets)
INCLUDE(CompilerConfig)
INCLUDE(Dependencies)

# Detect CI
IF(CI)
    MESSAGE("Automatic CI build")
ENDIF()

OPTION(STATIC "Build statically" OFF)
MESSAGE("VLC-Qt: Build statically: ${STATIC}")

# Link parameters
IF(STATIC)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt${LS}.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.a)
ELSEIF(MINGW)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt${LS}.dll.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.dll.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.dll.a)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt${LS}.dylib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.dylib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.dylib)
ELSEIF(MSVC)
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/vlc-qt${LS}.lib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/vlc-qt-widgets${LS}.lib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/vlc-qt-qml${LS}.lib)
ELSE()
    SET(VLCQT_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt${LS}.so)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.so)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.so)
ENDIF()


###################
# Compile and set #
###################
ADD_SUBDIRECTORY(src) 
ADD_SUBDIRECTORY(docs)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    ADD_SUBDIRECTORY(platform/pkgconfig)
ELSEIF(MINGW OR MSVC)
    ADD_SUBDIRECTORY(platform/windows)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ADD_SUBDIRECTORY(platform/osx)
ENDIF()


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build tests" OFF)
MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

IF(${BUILD_TESTS})
    ADD_SUBDIRECTORY(tests)
ENDIF()
