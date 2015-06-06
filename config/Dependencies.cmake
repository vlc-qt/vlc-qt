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
# Qt
IF(NOT DEFINED QT_VERSION)
    SET(QT_VERSION 5)
ENDIF()

IF(QT_VERSION MATCHES 4)
    FIND_PACKAGE(Qt4 4.8.0 REQUIRED)

    MESSAGE("VLC-Qt: Build with Qt4")
ELSE()
    FIND_PACKAGE(Qt5Core 5.2.0 REQUIRED)
    FIND_PACKAGE(Qt5Quick 5.2.0 REQUIRED)
    FIND_PACKAGE(Qt5Widgets 5.2.0 REQUIRED)

    MESSAGE("VLC-Qt: Build with Qt5")
ENDIF()

IF(QT_VERSION MATCHES 5)
    IF(MINGW OR MSVC)
        OPTION(WITH_ANGLE "Build with Angle" OFF)
        MESSAGE("VLC-Qt: Build with Angle: ${WITH_ANGLE}")

        IF(WITH_ANGLE)
            SET(WITH_GLES ON)
        ELSE()
            OPTION(WITH_GLES "Build with OpenGL ES2" OFF)
        ENDIF()
    ELSE()
        OPTION(WITH_GLES "Build with OpenGL ES2" OFF)
    ENDIF()

    MESSAGE("VLC-Qt: Build with OpenGL ES2: ${WITH_GLES}")
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    OPTION(WITH_X11 "Link with X11" OFF)
    MESSAGE("VLC-Qt: Link with X11: ${WITH_X11}")
ENDIF()

# Add libVLC libraries
# Define version, if not defined use latest relased
IF(NOT DEFINED LIBVLC_VERSION)
    SET(LIBVLC_VERSION 0x020200)
ENDIF()
# Include libVLC library
FIND_PACKAGE(LIBVLC REQUIRED)

# Set Qt bin dir to find QtCoreX.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_MOC_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes
