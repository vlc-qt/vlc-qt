#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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
    ${CMAKE_SOURCE_DIR}/config/platform
)

INCLUDE(ParseVersion)

PROJECT(VLC-Qt
        VERSION ${VLCQT_VERSION})

SET(PROJECT_LIBRARY VLCQt)
SET(PROJECT_AUTHOR "Tadej Novak")
SET(PROJECT_COPYRIGHT "Copyright (C) 2016 ${PROJECT_AUTHOR}.")
SET(PROJECT_DESCRIPTION "VLC-Qt - Qt bindings for libVLC")

SET(VLCQT_CORE Core)
SET(VLCQT_WIDGETS Widgets)
SET(VLCQT_QML Qml)
SET(VLCQT_PLUGIN_QML PluginQml)
SET(VLCQT_TEST ${PROJECT_NAME})
SET(VLCQT_CORE_NAME ${PROJECT_LIBRARY}Core)
SET(VLCQT_WIDGETS_NAME ${PROJECT_LIBRARY}Widgets)
SET(VLCQT_QML_NAME ${PROJECT_LIBRARY}Qml)
SET(VLCQT_PLUGIN_QML_NAME ${PROJECT_LIBRARY})
IF(MINGW)
    SET(VLCQT_PLUGIN_QML_BINARY_NAME lib${VLCQT_PLUGIN_QML_NAME})
ELSE()
    SET(VLCQT_PLUGIN_QML_BINARY_NAME ${VLCQT_PLUGIN_QML_NAME})
ENDIF()

INCLUDE(Macros)
INCLUDE(CustomTargets)
INCLUDE(CompilerConfig)
INCLUDE(Dependencies)
INCLUDE(Platform)

IF(NOT IOS)
    OPTION(STATIC "Build statically" OFF)
    MESSAGE("VLC-Qt: Build statically: ${STATIC}")
ELSE()
    SET(STATIC ON)
ENDIF()

# Link parameters
IF(STATIC)
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/lib${VLCQT_CORE_NAME}${LS}.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/lib${VLCQT_WIDGETS_NAME}${LS}.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/lib${VLCQT_QML_NAME}${LS}.a)
ELSEIF(MINGW)
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/lib${VLCQT_CORE_NAME}${LS}.dll.a)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/lib${VLCQT_WIDGETS_NAME}${LS}.dll.a)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/lib${VLCQT_QML_NAME}${LS}.dll.a)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/${VLCQT_CORE_NAME}.framework/Versions/${VLCQT_VERSION}/${VLCQT_CORE_NAME})
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/${VLCQT_WIDGETS_NAME}.framework/Versions/${VLCQT_VERSION}/${VLCQT_WIDGETS_NAME})
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.framework/Versions/${VLCQT_VERSION}/${VLCQT_QML_NAME})
ELSEIF(MSVC)
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/${VLCQT_CORE_NAME}${LS}.lib)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/${VLCQT_WIDGETS_NAME}${LS}.lib)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}${LS}.lib)
ELSE()
    SET(VLCQT_CORE_BINARY ${CMAKE_BINARY_DIR}/src/core/lib${VLCQT_CORE_NAME}${LS}.so)
    SET(VLCQT_WIDGETS_BINARY ${CMAKE_BINARY_DIR}/src/widgets/lib${VLCQT_WIDGETS_NAME}${LS}.so)
    SET(VLCQT_QML_BINARY ${CMAKE_BINARY_DIR}/src/qml/lib${VLCQT_QML_NAME}${LS}.so)
ENDIF()


###################
# Compile and set #
###################
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(docs)


#########
# Tests #
#########
IF(QT_VERSION MATCHES 5)
    OPTION(BUILD_TESTS "Build tests" OFF)
    MESSAGE("\nVLC-Qt: Build tests: ${BUILD_TESTS}\n")

    IF(BUILD_TESTS)
        ENABLE_TESTING(true)
        ADD_SUBDIRECTORY(tests)

        IF(NOT MSVC)
            OPTION(COVERAGE "Coverage report" OFF)
            MESSAGE("\nVLC-Qt: Coverage report: ${COVERAGE}\n")
        ENDIF()
    ENDIF()

    IF(COVERAGE)
        INCLUDE(CodeCoverage)
        SETUP_TARGET_FOR_COVERAGE(coverage ${CMAKE_CTEST_COMMAND} "${CMAKE_BINARY_DIR}/coverage")
    ENDIF()
ENDIF()

##################################
# CMake Package files generation #
##################################
INCLUDE(Package)
