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
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/config/platform
    ${CMAKE_MODULE_PATH}
)

mark_as_advanced(BUILD_TESTING)

SET(VLCQt_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
SET(VLCQT_CORE_NAME ${PROJECT_LIBRARY}Core)
SET(VLCQT_WIDGETS_NAME ${PROJECT_LIBRARY}Widgets)
SET(VLCQT_QML_NAME ${PROJECT_LIBRARY}Qml)
SET(VLCQT_PLUGIN_QML_NAME ${PROJECT_LIBRARY})

INCLUDE(GNUInstallDirs)
INCLUDE(Macros)
INCLUDE(CompilerConfig)
INCLUDE(Dependencies)
INCLUDE(Platform)


###################
# Compile and set #
###################
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(docs)


#########
# Tests #
#########
IF(BUILD_TESTING)
    IF(QT_VERSION MATCHES 5 AND NOT MOBILE)
        ENABLE_TESTING(true)
        ADD_SUBDIRECTORY(tests)

        IF(NOT MSVC)
            SET(COVERAGE OFF CACHE BOOL "Coverage report")
        ENDIF()

        IF(COVERAGE)
            MESSAGE(STATUS "Generate coverage report using 'coverage' target")
            INCLUDE(CodeCoverage)
            SETUP_TARGET_FOR_COVERAGE(coverage ${CMAKE_CTEST_COMMAND} "${CMAKE_BINARY_DIR}/coverage")
        ENDIF()
    ENDIF()
ENDIF()

##################################
# CMake Package files generation #
##################################
INCLUDE(Package)
