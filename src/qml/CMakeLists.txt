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
        ${VLCQT_QML_NAME}.rc.in
        ${VLCQT_QML_NAME}.rc
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
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/include
)

INCLUDE_DIRECTORIES(
    ${LIBVLC_INCLUDE_DIR}
    ${LIBVLC_INCLUDE_DIR}/vlc/plugins
)


# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.rc
        -o ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/qml"
    )
    SET(VLCQT_QML_SRCS ${VLCQT_QML_SRCS} ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.obj)
ENDIF()

IF(MSVC)
    SET(VLCQT_QML_SRCS ${VLCQT_QML_SRCS} ${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.rc)
ENDIF()

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_QML} STATIC ${VLCQT_QML_SRCS} ${VLCQT_QML_HEADERS})
ELSE()
    ADD_LIBRARY(${VLCQT_QML} SHARED ${VLCQT_QML_SRCS} ${VLCQT_QML_HEADERS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_QML} ${VLCQT_CORE})

# MSVC: Fix build
IF(MSVC)
    ADD_DEFINITIONS(-DNOMINMAX)
ENDIF()

# Linux/Mac: Set framework, version and headers
SET_TARGET_PROPERTIES(${VLCQT_QML} PROPERTIES FRAMEWORK ON
                                              OUTPUT_NAME "${VLCQT_QML_NAME}"
                                              VERSION ${VLCQT_VERSION}
                                              SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                                              PUBLIC_HEADER "${VLCQT_QML_HEADERS}"
)

# Link the required libraries
TARGET_LINK_LIBRARIES(${VLCQT_QML} PRIVATE Qt5::Quick)
IF(NOT STATIC)
    TARGET_LINK_LIBRARIES(${VLCQT_QML} PRIVATE ${VLCQT_CORE_BINARY} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
    IF(Qt5Core_VERSION VERSION_LESS "5.5.0" AND WITH_GLES)
        IF(MSVC)
            TARGET_LINK_LIBRARIES(${VLCQT_QML} PRIVATE
                                  ${_qt5Core_install_prefix}/lib/libEGL${LE}.lib
                                  ${_qt5Core_install_prefix}/lib/libGLESv2${LE}.lib)
        ENDIF()
        IF(MINGW)
            TARGET_LINK_LIBRARIES(${VLCQT_QML} PRIVATE
                                  ${_qt5Core_install_prefix}/lib/liblibEGL${LE}.a
                                  ${_qt5Core_install_prefix}/lib/liblibGLESv2${LE}.a)
        ENDIF()
    ENDIF()

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND WITH_X11)
        TARGET_LINK_LIBRARIES(${VLCQT_QML} PRIVATE -lX11)
    ENDIF()
ENDIF()


################
# Installation #
################
IF(NOT STATIC AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQtQmlIncludesLocation lib/${VLCQT_QML_NAME}.framework)
    SET(VLCQtQmlPublicHeaderLocation lib/${VLCQT_QML_NAME}.framework)
ELSE()
    SET(VLCQtQmlIncludesLocation include)
    SET(VLCQtQmlPublicHeaderLocation include/${VLCQT_QML_NAME})
ENDIF()

INSTALL(TARGETS ${VLCQT_QML} EXPORT VLCQtQmlTargets
        RUNTIME DESTINATION bin
        FRAMEWORK DESTINATION lib${LIB_SUFFIX}
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        INCLUDES DESTINATION ${VLCQtQmlIncludesLocation}
        PUBLIC_HEADER DESTINATION ${VLCQtQmlPublicHeaderLocation}
)
