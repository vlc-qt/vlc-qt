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
ADD_DEFINITIONS(-DVLCQT_QML_LIBRARY)

# Add definitions for shared library
ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/src/platform/windows/qml.rc.in
    ${CMAKE_BINARY_DIR}/src/platform/windows/qml.rc
)

###################
# List of sources #
###################
IF(QT5)
# Define the C++ source files
    SET(VLCQT_QML_SRCS
        QmlVideoPlayer.cpp
        QmlVideoPlayer5.h
    )

# Define the Include files
    SET(VLCQT_QML_HEADERS
        QmlVideoPlayer5.h
        SharedExportQml.h
    )
ELSE(QT5)
# Define the C++ source files
    SET(VLCQT_QML_SRCS
        QmlVideoPlayer.cpp
        QmlVideoPlayer4.h
    )

# Define the Include files
    SET(VLCQT_QML_HEADERS
        QmlVideoPlayer4.h
        SharedExportQml.h
    )
ENDIF(QT5)


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_BINARY_DIR}/src
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ENDIF(MSVC)

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
ENDIF(MINGW)

IF(MSVC)
    SET(VLCQT_QML_SRCS ${VLCQT_QML_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/qml.rc)
ENDIF(MSVC)

# Create the library.
ADD_LIBRARY(${VLCQT_QML_SHARED} SHARED ${VLCQT_QML_SRCS})

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF(MSVC)

# Linux: So version extensions
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET_TARGET_PROPERTIES(${VLCQT_QML_SHARED} PROPERTIES VERSION ${VLCQT_VERSION}
                                              SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Link the required libraries
IF(QT5)
    QT5_USE_MODULES(${VLCQT_QML_SHARED} Quick)
ELSE(QT5)
    TARGET_LINK_LIBRARIES(${VLCQT_QML_SHARED} ${QT_LIBRARIES})
ENDIF(QT5)


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_QML_SHARED} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_QML_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
