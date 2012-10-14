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

# Add definition for exporting symbols
ADD_DEFINITIONS(-DVLCQT_LIBRARY)

# Add definitions for shared library
ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/src/Config.h.in
    ${CMAKE_BINARY_DIR}/src/Config.h
    @ONLY
)


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_CORE_SRCS
    core/Audio.cpp
    core/Common.cpp
    core/Enums.cpp
    core/Error.cpp
    core/Instance.cpp
    core/Media.cpp
    core/MediaList.cpp
    core/MediaListPlayer.cpp
    core/MediaPlayer.cpp
    core/MetaManager.cpp
    core/Video.cpp
)

SET(VLCQT_GUI_SRCS
    gui/AudioControl.cpp
    gui/SeekWidget.cpp
    gui/VideoControl.cpp
    gui/VideoWidget.cpp
    gui/VolumeSlider.cpp
)

SET(VLCQT_QML_SRCS
    qml/QMLVideoPlayer.cpp
)

# Define the Include files
SET(VLCQT_HEADERS
    core/Audio.h
    core/Common.h
    core/Enums.h
    core/Error.h
    core/Instance.h
    core/Media.h
    core/MediaList.h
    core/MediaListPlayer.h
    core/MediaPlayer.h
    core/MetaManager.h
    core/SharedExport.h
    core/Video.h

    gui/AudioControl.h
    gui/SeekWidget.h
    gui/VideoControl.h
    gui/VideoWidget.h
    gui/VolumeSlider.h

    ${CMAKE_BINARY_DIR}/src/Config.h
)

IF(WITH_QML)
    SET(VLCQT_HEADERS
        ${VLCQT_HEADERS}

        qml/QMLVideoPlayer.h
    )
ENDIF(WITH_QML)

# Define the resource files
SET(VLCQT_RESOURCES
    ../data/logo.qrc
)


#####################
# Compiler settings #
#####################
# This scripts run the resource compiler rcc
IF(WITH_QT5)
    QT5_ADD_RESOURCES(VLCQT_RESOURCES_SRCS ${VLCQT_RESOURCES})
ELSE(WITH_QT5)
    QT4_ADD_RESOURCES(VLCQT_RESOURCES_SRCS ${VLCQT_RESOURCES})
ENDIF(WITH_QT5)

INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_BINARY_DIR}/src
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ENDIF(MSVC)

# Create the library.
IF(WITH_QT5)
    ADD_LIBRARY(${VLCQT_SHARED} SHARED
                ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS} ${VLCQT_RESOURCES_SRCS})
ELSE(WITH_QT5)
    IF(WITH_QML)
        ADD_LIBRARY(${VLCQT_SHARED} SHARED
                    ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS} ${VLCQT_QML_SRCS} ${VLCQT_RESOURCES_SRCS})
    ELSE(WITH_QML)
        ADD_LIBRARY(${VLCQT_SHARED} SHARED
                    ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS} ${VLCQT_RESOURCES_SRCS})
    ENDIF(WITH_QML)
ENDIF(WITH_QT5)

# avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF(MSVC)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_SHARED} PROPERTIES VERSION ${VLCQT_VERSION}
                                          SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Link the required libraries
IF(WITH_QT5)
    QT5_USE_MODULES(${VLCQT_SHARED} Widgets)
    TARGET_LINK_LIBRARIES(${VLCQT_SHARED} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ELSE(WITH_QT5)
    TARGET_LINK_LIBRARIES(${VLCQT_SHARED} ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ENDIF(WITH_QT5)

# On Mac OS X, the VideoWidget uses Objective-C and Cocoa
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_SOURCE_FILES_PROPERTIES(gui/VideoWidget.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
    FIND_PATH(COCOA_INCLUDE_DIR Cocoa/Cocoa.h)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    SET(EXTRA_LIBS ${COCOA_LIBRARY})
    TARGET_LINK_LIBRARIES(${VLCQT_SHARED} ${COCOA_LIBRARY})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_SHARED} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
