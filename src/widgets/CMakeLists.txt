#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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
ADD_DEFINITIONS(-DVLCQT_WIDGETS_LIBRARY)

# Add definitions for shared library
ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_WIDGETS_SRCS
    ControlAudio.cpp
    ControlVideo.cpp
    WidgetSeek.cpp
    WidgetVideo.cpp
    WidgetVolumeSlider.cpp
)

# Define the Include files
SET(VLCQT_WIDGETS_HEADERS
    ControlAudio.h
    ControlVideo.h
    SharedExportWidgets.h
    WidgetSeek.h
    WidgetVideo.h
    WidgetVolumeSlider.h
)


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/widgets
    ${CMAKE_BINARY_DIR}/src
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ENDIF(MSVC)

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_SOURCE_DIR}/src/platform/windows/widgets.rc
        -o ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/platform/windows"
    )
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj)
ENDIF(MINGW)

IF(MSVC)
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_SOURCE_DIR}/src/platform/windows/widgets.rc)
ENDIF(MSVC)

# Create the library.
ADD_LIBRARY(${VLCQT_WIDGETS_SHARED} SHARED ${VLCQT_WIDGETS_SRCS})

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF(MSVC)

# Linux: So version extensions
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS_SHARED} PROPERTIES VERSION ${VLCQT_VERSION}
                                                  SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Link the required libraries
IF(QT5)
    QT5_USE_MODULES(${VLCQT_WIDGETS_SHARED} Widgets)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS_SHARED} ${VLCQT_BINARY})
ELSE(QT5)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS_SHARED} ${QT_LIBRARIES} ${VLCQT_BINARY})
ENDIF(QT5)

# On Mac OS X, the VideoWidget uses Objective-C and Cocoa
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_SOURCE_FILES_PROPERTIES(VideoWidget.cpp PROPERTIES COMPILE_FLAGS "-x objective-c++")
    FIND_PATH(COCOA_INCLUDE_DIR Cocoa/Cocoa.h)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    SET(EXTRA_LIBS ${COCOA_LIBRARY})
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS_SHARED} ${COCOA_LIBRARY})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_WIDGETS_SHARED} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_WIDGETS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
