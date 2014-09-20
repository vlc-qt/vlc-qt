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
ADD_DEFINITIONS(-DVLCQT_QML_LIBRARY)

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF()

IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/src/platform/windows/qml.rc.in
        ${CMAKE_BINARY_DIR}/src/platform/windows/qml.rc
    )
ENDIF()

###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_QML_SRCS
    QmlVideoObject.cpp
    QmlVideoPlayer.cpp
    SharedExportQml.h

    painter/GlPainter.cpp
    painter/GlslPainter.cpp
)

# Define the Include files
SET(VLCQT_QML_HEADERS
    QmlVideoObject.h
    QmlVideoPlayer.h
    SharedExportQml.h
)

SET(VLCQT_QML_SRCS
    ${VLCQT_QML_SRCS}
    ${VLCQT_QML_HEADERS}
)


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_BINARY_DIR}/src
)

INCLUDE_DIRECTORIES(
    ${LIBVLC_INCLUDE_DIR}
    ${LIBVLC_INCLUDE_DIR}/vlc/plugins
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ELSEIF(MINGW)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/mingw)
ENDIF()

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/src/platform/windows/qml.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/src/platform/windows/qml.rc
        -o ${CMAKE_BINARY_DIR}/src/platform/windows/qml.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/platform/windows"
    )
    SET(VLCQT_QML_SRCS ${VLCQT_QML_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/qml.obj)
ENDIF()

IF(MSVC)
    SET(VLCQT_QML_SRCS ${VLCQT_QML_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/qml.rc)
ENDIF()

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_QML} STATIC ${VLCQT_QML_SRCS})
ELSE()
    ADD_LIBRARY(${VLCQT_QML} SHARED ${VLCQT_QML_SRCS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_QML} ${VLCQT})

# Debug suffix
IF(DEBUG_SUFFIX)
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES DEBUG_POSTFIX ${LS})
ENDIF()

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF()

# MSVC: Fix build
IF(MSVC)
    ADD_DEFINITIONS(-DNOMINMAX)
ENDIF()

# Linux: So version extensions
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES VERSION ${VLCQT_VERSION}
                                                  SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF()

# Link the required libraries
TARGET_LINK_LIBRARIES(${VLCQT_QML} Qt5::Quick ${VLCQT_BINARY} ${LIBVLCCORE_LIBRARY})

IF(WITH_QML_GLES)
    IF(MSVC)
        TARGET_LINK_LIBRARIES(${VLCQT_QML}
                              ${_qt5Core_install_prefix}/lib/libEGL${LE}.lib
                              ${_qt5Core_install_prefix}/lib/libGLESv2${LE}.lib)
    ENDIF()
    IF(MINGW)
        TARGET_LINK_LIBRARIES(${VLCQT_QML}
                              ${_qt5Core_install_prefix}/lib/liblibEGL${LE}.a
                              ${_qt5Core_install_prefix}/lib/liblibGLESv2${LE}.a)
    ENDIF()
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND NOT STATIC)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_QML} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change ${VLCQT_BINARY} "@loader_path/../lib/libvlc-qt.dylib" $<TARGET_FILE:${VLCQT_QML}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_QML} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlc.5.dylib" "@loader_path/../lib/libvlc.5.dylib" $<TARGET_FILE:${VLCQT_QML}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_QML} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlccore.5.dylib" "@loader_path/../lib/libvlccore.5.dylib" $<TARGET_FILE:${VLCQT_QML}>)
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_QML} POST_BUILD COMMAND
        ${CMAKE_INSTALL_NAME_TOOL} -change "@loader_path/lib/libvlccore.7.dylib" "@loader_path/../lib/libvlccore.7.dylib" $<TARGET_FILE:${VLCQT_QML}>)
ENDIF()


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_QML} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_QML_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
