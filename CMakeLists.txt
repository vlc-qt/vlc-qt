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
    ${CMAKE_SOURCE_DIR}/platform
)

INCLUDE(ParseVersion)

PROJECT(vlc-qt
        VERSION ${VLCQT_VERSION})

SET(PROJECT_NAME_OUT VLC-Qt)
SET(PROJECT_AUTHOR "Tadej Novak")
SET(PROJECT_COPYRIGHT "Copyright (C) 2015 ${PROJECT_AUTHOR}.")
SET(PROJECT_DESCRIPTION "VLC-Qt - Qt bindings for libVLC")

SET(VLCQT_CORE ${PROJECT_NAME}-core)
SET(VLCQT_WIDGETS ${PROJECT_NAME}-widgets)
SET(VLCQT_QML ${PROJECT_NAME}-qml)
SET(VLCQT_TEST ${PROJECT_NAME_OUT})

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
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt-core${LS}.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.a)
ELSEIF(MINGW)
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt-core${LS}.dll.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.dll.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.dll.a)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/vlc-qt-core.framework)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/vlc-qt-widgets.framework)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/vlc-qt-qml.framework)
ELSEIF(MSVC)
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/vlc-qt-core${LS}.lib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/vlc-qt-widgets${LS}.lib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/vlc-qt-qml${LS}.lib)
ELSE()
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/libvlc-qt-core${LS}.so)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/libvlc-qt-widgets${LS}.so)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/libvlc-qt-qml${LS}.so)
ENDIF()


###################
# Compile and set #
###################
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    INCLUDE(pkgconfig)
ELSEIF(MINGW OR MSVC)
    INCLUDE(Windows)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    INCLUDE(OSX)
ENDIF()
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(docs)


#########
# Tests #
#########
OPTION(BUILD_TESTS "Build tests" OFF)
MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

IF(${BUILD_TESTS})
    ADD_SUBDIRECTORY(tests)
ENDIF()
