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

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE(STATIC)
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF(STATIC)

IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/src/platform/windows/widgets.rc.in
        ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.rc
    )
ENDIF(MINGW OR MSVC)

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
ENDIF(MSVC)

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.rc
        -o ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/platform/windows"
    )
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.obj)
ENDIF(MINGW)

IF(MSVC)
    SET(VLCQT_WIDGETS_SRCS ${VLCQT_WIDGETS_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/widgets.rc)
ENDIF(MSVC)

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_WIDGETS} STATIC ${VLCQT_WIDGETS_SRCS})
ELSE(STATIC)
    ADD_LIBRARY(${VLCQT_WIDGETS} SHARED ${VLCQT_WIDGETS_SRCS})
ENDIF(STATIC)
ADD_DEPENDENCIES(${VLCQT_WIDGETS} ${VLCQT})

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF(MSVC)

# Linux: So version extensions
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES VERSION ${VLCQT_VERSION}
                                                  SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Link the required libraries
IF(QT5)
    QT5_USE_MODULES(${VLCQT_WIDGETS} Widgets)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} ${VLCQT_BINARY})
ELSE(QT5)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} ${QT_LIBRARIES} ${VLCQT_BINARY})
ENDIF(QT5)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND NOT STATIC)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_WIDGETS} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change ${VLCQT_BINARY} "@loader_path/../lib/libvlc-qt.dylib" $<TARGET_FILE:${VLCQT_WIDGETS}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_WIDGETS} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlc.5.dylib" "@loader_path/../lib/libvlc.5.dylib" $<TARGET_FILE:${VLCQT_WIDGETS}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_WIDGETS} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlccore.5.dylib" "@loader_path/../lib/libvlccore.5.dylib" $<TARGET_FILE:${VLCQT_WIDGETS}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_WIDGETS} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlccore.7.dylib" "@loader_path/../lib/libvlccore.7.dylib" $<TARGET_FILE:${VLCQT_WIDGETS}>)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND NOT STATIC)


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_WIDGETS} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_WIDGETS_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
