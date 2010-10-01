#############################################################################
# VLC-Qt - Qt and libvlc connector library
#############################################################################
# Copyright (C) 2008-2010 Tadej Novak
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# This file may be used under the terms of the
# GNU General Public License version 3.0 as published by the
# Free Software Foundation and appearing in the file LICENSE.GPL
# included in the packaging of this file.
#############################################################################

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
# Set your list of sources here.
SET(VLCQT_SRCS
	core/Audio.cpp
	core/Error.cpp
	core/Instance.cpp
	core/Media.cpp
	core/MediaPlayer.cpp
	core/Video.cpp
	gui/AudioControl.cpp
	gui/SeekWidget.cpp
	gui/VolumeSlider.cpp
	gui/VideoControl.cpp
	gui/VideoWidget.cpp
)

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

SET(VLCQT_HEADERS
	${VLCQT_MOCS}
	core/Audio.h
	core/Error.h
	core/Video.h
	${CMAKE_BINARY_DIR}/src/Config.h
)

INCLUDE(${QT_USE_FILE})
QT4_WRAP_CPP(VLCQT_MOCS_SRCS ${VLCQT_MOCS})

INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})

# Create the library.
ADD_LIBRARY(${PROJECT_NAME} SHARED ${VLCQT_SRCS} ${VLCQT_MOCS_SRCS})

IF(PACKAGE)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VERSION ${VLCQT_VERSION}
									  SOVERSION 0.4)
ENDIF(PACKAGE)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})


################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin
					LIBRARY DESTINATION lib${LIB_SUFFIX}
					ARCHIVE DESTINATION lib${LIB_SUFFIX})
INSTALL(FILES ${VLCQT_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
