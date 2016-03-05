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
# Configuration #
#################

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/docs/Doxyfile.in"
    "${CMAKE_BINARY_DIR}/docs/Doxyfile"
    @ONLY
)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/CHANGELOG.md"
    "${CMAKE_BINARY_DIR}/docs/changelog.md"
    COPYONLY)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/docs/index.md"
    "${CMAKE_BINARY_DIR}/docs/index.md"
    COPYONLY)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/BUILDING.md"
    "${CMAKE_BINARY_DIR}/docs/building.md"
    COPYONLY)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/docs/contributing.md"
    "${CMAKE_BINARY_DIR}/docs/contributing.md"
    COPYONLY)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/LICENSE.md"
    "${CMAKE_BINARY_DIR}/docs/license.md"
    COPYONLY)
