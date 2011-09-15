#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2011 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Configuration #
#################

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/src/Config.h.in"
    "${CMAKE_BINARY_DIR}/src/Config.h"
    @ONLY
)

INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/src" "${CMAKE_SOURCE_DIR}/src")


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_SRCS
    core/Audio.cpp
    core/Common.cpp
    core/Enums.cpp
    core/Error.cpp
    core/Instance.cpp
    core/Media.cpp
    core/MediaPlayer.cpp
    core/MetaManager.cpp
    core/Video.cpp

    gui/AudioControl.cpp
    gui/SeekWidget.cpp
    gui/VideoControl.cpp
    gui/VideoWidget.cpp
    gui/VolumeSlider.cpp
)

# Define the MOC source files
SET(VLCQT_MOCS
    core/Audio.h
    core/Instance.h
    core/Media.h
    core/MediaPlayer.h
    core/Video.h

    gui/AudioControl.h
    gui/SeekWidget.h
    gui/VideoControl.h
    gui/VideoWidget.h
    gui/VolumeSlider.h
)

# Define the Include files
SET(VLCQT_HEADERS
    ${VLCQT_MOCS}

    core/Common.h
    core/Enums.h
    core/Error.h
    core/MetaManager.h

    ${CMAKE_BINARY_DIR}/src/Config.h
)

#####################
# Compiler settings #
#####################
# Include required directories
INCLUDE(${QT_USE_FILE})
QT4_WRAP_CPP(VLCQT_MOCS_SRCS ${VLCQT_MOCS})

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src/core" "${CMAKE_SOURCE_DIR}/src/gui" ${LIBVLC_INCLUDE_DIR})

# Create the library.
ADD_LIBRARY(${VLCQT_SHARED} SHARED ${VLCQT_SRCS} ${VLCQT_MOCS_SRCS})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES VERSION ${VLCQT_VERSION}
                                          SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

TARGET_LINK_LIBRARIES(${VLCQT_SHARED} ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_SHARED} RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib${LIB_SUFFIX}
                    ARCHIVE DESTINATION lib${LIB_SUFFIX})
INSTALL(FILES ${VLCQT_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
