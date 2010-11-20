#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Configuration #
#################

CONFIGURE_FILE(
	"${CMAKE_SOURCE_DIR}/src/Config.h.in"
	"${CMAKE_BINARY_DIR}/src/Config.h"
)

CONFIGURE_FILE(
	"${CMAKE_SOURCE_DIR}/doc/Doxyfile.in"
	"${CMAKE_BINARY_DIR}/doc/Doxyfile"
)

INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/src" "${CMAKE_SOURCE_DIR}/src")


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_SRCS
	core/Audio.cpp
	core/Common.cpp
	core/Error.cpp
	core/Instance.cpp
	core/Media.cpp
	core/MediaPlayer.cpp
	core/MetaManager.cpp
	core/Video.cpp
	gui/AudioControl.cpp
	gui/SeekWidget.cpp
	gui/VolumeSlider.cpp
	gui/VideoControl.cpp
	gui/VideoWidget.cpp
)

# Define the MOC source files
SET(VLCQT_MOCS
	core/Instance.h
	core/Media.h
	core/MediaPlayer.h
	gui/AudioControl.h
	gui/SeekWidget.h
	gui/VolumeSlider.h
	gui/VideoControl.h
	gui/VideoWidget.h
)

# Define the Include files
SET(VLCQT_HEADERS
	${VLCQT_MOCS}
	core/Audio.h
	core/Common.h
	core/Error.h
	core/MetaManager.h
	core/Video.h
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
ADD_LIBRARY(${PROJECT_NAME} SHARED ${VLCQT_SRCS} ${VLCQT_MOCS_SRCS})

IF(PACKAGE)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION ${VLCQT_VERSION}
									  SOVERSION 0.5)
ENDIF(PACKAGE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})


################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin
					LIBRARY DESTINATION lib${LIB_SUFFIX}
					ARCHIVE DESTINATION lib${LIB_SUFFIX})
INSTALL(FILES ${VLCQT_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
