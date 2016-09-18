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
# Version #
###########
# VLC-Qt version number
FILE(READ VERSION VLCQT_VERSION)
STRING(REGEX REPLACE "\n" "" VLCQT_VERSION "${VLCQT_VERSION}") # get rid of the newline at the end
MESSAGE(STATUS "Building VLC-Qt ${VLCQT_VERSION}")

# Find Git Version Patch
FIND_PROGRAM(GIT git)
IF(GIT AND NOT NO_GIT)
    EXECUTE_PROCESS(
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${GIT} rev-parse --short HEAD
        OUTPUT_VARIABLE GIT_OUT OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    IF(NOT GIT_OUT STREQUAL "")
        SET(PROJECT_VERSION_VCS "${GIT_OUT}")
        MESSAGE(STATUS "Git revision: ${PROJECT_VERSION_VCS}")
    ENDIF()
ELSEIF(GITBUILD)
    SET(PROJECT_VERSION_VCS "${GITBUILD}")
    MESSAGE(STATUS "Git revision: ${PROJECT_VERSION_VCS}")
ELSE()
    SET(GIT_OUT 0)
ENDIF()
