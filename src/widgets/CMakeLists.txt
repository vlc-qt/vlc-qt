#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2014 Tadej Novak <tadej@tano.si>
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

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF()

IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/platform/windows/widgets.rc.in
        ${CMAKE_BINARY_DIR}/platform/windows/widgets.rc
    )
ENDIF()

###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_WIDGETS_SRCS
    ControlAudio.cpp
    ControlVideo.cpp
    SharedExportWidgets.h
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
ENDIF()

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/platform/windows/widgets.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/platform/windows/widgets.rc
        -o ${CMAKE_BINARY_DIR}/platform/windows/widgets.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/platform/windows"
    )
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_BINARY_DIR}/platform/windows/widgets.obj)
ENDIF()

IF(MSVC)
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_BINARY_DIR}/platform/windows/widgets.rc)
ENDIF()

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_WIDGETS} STATIC ${VLCQT_WIDGETS_SRCS})
ELSE()
    ADD_LIBRARY(${VLCQT_WIDGETS} SHARED ${VLCQT_WIDGETS_SRCS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_WIDGETS} ${VLCQT_CORE})

# Debug suffix
IF(DEBUG_SUFFIX)
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES DEBUG_POSTFIX ${LS})
ENDIF()

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF()

# Linux/Mac: Set framework, version and headers
SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES FRAMEWORK ON
                                                  VERSION ${VLCQT_VERSION}
                                                  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                                                  PUBLIC_HEADER "${VLCQT_WIDGETS_HEADERS}"
)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_WIDGETS}
        COMMAND "${CMAKE_COMMAND}" -E create_symlink . vlc-qt
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src/widgets/${VLCQT_WIDGETS}.framework/Headers"
    )
ENDIF()

# Link the required libraries
IF(QT_VERSION MATCHES 4)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} ${VLCQT_CORE_BINARY} Qt4::QtGui)
ELSE()
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} ${VLCQT_CORE_BINARY} Qt5::Widgets)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND WITH_X11)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} -lX11)
ENDIF()


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_WIDGETS} RUNTIME DESTINATION bin
        FRAMEWORK DESTINATION lib${LIB_SUFFIX}
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        PUBLIC_HEADER DESTINATION include/vlc-qt
)
