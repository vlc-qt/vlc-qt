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

# Define the MOC source files
SET(VLCQT_CORE_MOCS
    core/Audio.h
    core/Instance.h
    core/Media.h
    core/MediaList.h
    core/MediaListPlayer.h
    core/MediaPlayer.h
    core/Video.h
)

SET(VLCQT_GUI_MOCS
    gui/AudioControl.h
    gui/SeekWidget.h
    gui/VideoControl.h
    gui/VideoWidget.h
    gui/VolumeSlider.h
)

SET(VLCQT_QML_MOCS
    qml/QMLVideoPlayer.h
)

# Define the Include files
SET(VLCQT_HEADERS
    ${VLCQT_CORE_MOCS}
    ${VLCQT_GUI_MOCS}

    core/Common.h
    core/Enums.h
    core/Error.h
    core/MetaManager.h
    core/SharedExport.h

    ${CMAKE_BINARY_DIR}/src/Config.h
)

IF(WITH_QML)
    SET(VLCQT_HEADERS
        ${VLCQT_HEADERS}

        ${VLCQT_QML_MOCS}
    )
ENDIF(WITH_QML)

# Define the resource files
SET(VLCQT_RESOURCES
    ../data/logo.qrc
)


#####################
# Compiler settings #
#####################
# Include required directories
IF(WITH_QT5)
    INCLUDE_DIRECTORIES(
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
    )
ELSE(WITH_QT5)
    IF(WITH_QML)
        SET(QT_USE_QTDECLARATIVE True)
    ENDIF(WITH_QML)
    INCLUDE(${QT_USE_FILE})
ENDIF(WITH_QT5)

# This scripts run the resource compiler rcc and the meta object compiler moc.
IF(WITH_QT5)
    QT5_ADD_RESOURCES(VLCQT_RESOURCES_SRCS ${VLCQT_RESOURCES})
    QT5_WRAP_CPP(VLCQT_MOCS_SRCS ${VLCQT_CORE_MOCS} ${VLCQT_GUI_MOCS})
ELSE(WITH_QT5)
    QT4_ADD_RESOURCES(VLCQT_RESOURCES_SRCS ${VLCQT_RESOURCES})
    IF(WITH_QML)
        QT4_WRAP_CPP(VLCQT_MOCS_SRCS ${VLCQT_CORE_MOCS} ${VLCQT_GUI_MOCS} ${VLCQT_QML_MOCS})
    ELSE(WITH_QML)
        QT4_WRAP_CPP(VLCQT_MOCS_SRCS ${VLCQT_CORE_MOCS} ${VLCQT_GUI_MOCS})
    ENDIF(WITH_QML)
ENDIF(WITH_QT5)

INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_BINARY_DIR}/src
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${MSINTTYPES_PATH})
ENDIF(MSVC)

# This line sets the required Qt libraries
IF(WITH_QT5)
    SET(VLCQT_QTLIB ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})
ELSE(WITH_QT5)
    SET(VLCQT_QTLIB ${QT_LIBRARIES})
ENDIF(WITH_QT5)

# Create the library.
IF(WITH_QT5)
    ADD_LIBRARY(${VLCQT_SHARED} SHARED
                ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS}
                ${VLCQT_MOCS_SRCS} ${VLCQT_RESOURCES_SRCS})
ELSE(WITH_QT5)
    IF(WITH_QML)
        ADD_LIBRARY(${VLCQT_SHARED} SHARED
                    ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS} ${VLCQT_QML_SRCS}
                    ${VLCQT_MOCS_SRCS} ${VLCQT_RESOURCES_SRCS})
    ELSE(WITH_QML)
        ADD_LIBRARY(${VLCQT_SHARED} SHARED
                    ${VLCQT_CORE_SRCS} ${VLCQT_GUI_SRCS}
                    ${VLCQT_MOCS_SRCS} ${VLCQT_RESOURCES_SRCS})
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
TARGET_LINK_LIBRARIES(${VLCQT_SHARED} ${VLCQT_QTLIB} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})

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
