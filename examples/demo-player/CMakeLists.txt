#############################################################################
# VLC-Qt Demo Player
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################

PROJECT(demo-player)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

SET(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
)

# Set MingW bin dir, if MingW present
IF(MINGW)
    STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR_TMP "${CMAKE_CXX_COMPILER}")
    STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR_TMP}") # Replace back slashes to slashes
ENDIF(MINGW)

# Find Qt
SET(QT_MIN_VERSION "4.8.0")
FIND_PACKAGE(Qt4)
IF(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)
    FIND_PACKAGE(Qt5Core REQUIRED)
    FIND_PACKAGE(Qt5Widgets REQUIRED)
    SET(QT5 1)
ELSE(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)
    SET(QT5 0)
ENDIF(NOT QT4_FOUND OR QT_VERSION_MAJOR MATCHES 5)

# Add additional libraries
FIND_PACKAGE(LIBVLCQT REQUIRED)

# Set Qt bin dir to find QtCore*.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_QMAKE_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes

# Include source
ADD_SUBDIRECTORY(src)
