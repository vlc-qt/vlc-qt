#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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
ADD_DEFINITIONS(-DVLCQT_PLUGIN_QML)

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATICPLUGIN -DQT_PLUGIN)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -DQT_PLUGIN)
ENDIF()

# Generate files
CONFIGURE_FILE(
    windows.bat.in
    windows.bat
    @ONLY
)

CONFIGURE_FILE(
    linux.sh.in
    linux.sh
    @ONLY
)


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_PLUGIN_QML_SRCS
    VLCQtPlugin.cpp
)

IF(STATIC)
    SET(VLCQT_PLUGIN_QML_SRCS
        ${VLCQT_PLUGIN_QML_SRCS}
        VLCQtPluginResource.qrc
    )
ENDIF()


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_SOURCE_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME}
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME}
    ${CMAKE_BINARY_DIR}/include
)

# Additional macros
GENERATE_WINDOWS_RC(${VLCQT_PLUGIN_QML_NAME} plugins/${VLCQT_PLUGIN_QML_NAME} VLCQT_PLUGIN_QML_SRCS)

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_PLUGIN_QML} STATIC ${VLCQT_PLUGIN_QML_SRCS})
    SET_TARGET_PROPERTIES(${VLCQT_PLUGIN_QML} PROPERTIES
        AUTOMOC_MOC_OPTIONS -Muri=${VLCQT_PLUGIN_QML_NAME})
ELSE()
    ADD_LIBRARY(${VLCQT_PLUGIN_QML} SHARED ${VLCQT_PLUGIN_QML_SRCS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_PLUGIN_QML} ${VLCQT_QML})

# Linux/Mac: Set framework, version and headers
SET_TARGET_PROPERTIES(${VLCQT_PLUGIN_QML} PROPERTIES FRAMEWORK OFF
                                          OUTPUT_NAME "${VLCQT_PLUGIN_QML_NAME}"
                                          VERSION ${VLCQT_VERSION}
                                          SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)
IF(MINGW)
    SET_TARGET_PROPERTIES(${VLCQT_PLUGIN_QML} PROPERTIES PREFIX "")
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(${VLCQT_PLUGIN_QML} PROPERTIES INSTALL_RPATH "@loader_path/../../lib")
ENDIF()

# Link the required libraries
TARGET_LINK_LIBRARIES(${VLCQT_PLUGIN_QML} PRIVATE Qt5::Quick ${VLCQT_CORE} ${VLCQT_QML})

# Generate type info
FILE(COPY qmldir DESTINATION ${CMAKE_BINARY_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME})


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_PLUGIN_QML}
    RUNTIME DESTINATION qml/${VLCQT_PLUGIN_QML_NAME}
    LIBRARY DESTINATION qml/${VLCQT_PLUGIN_QML_NAME}
    ARCHIVE DESTINATION qml/${VLCQT_PLUGIN_QML_NAME}
)

INSTALL(FILES qmldir DESTINATION qml/${VLCQT_PLUGIN_QML_NAME})
IF(NOT STATIC)
    IF(MSVC OR MINGW)
        IF(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
            INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_BINARY_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME}/windows.bat WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/qml)")
        ENDIF()
    ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_BINARY_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME}/linux.sh WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/qml)")
    ELSEIF(NOT MOBILE)
        INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${QT_BIN_DIR}/qmlplugindump -nonrelocatable ${VLCQT_PLUGIN_QML_NAME} 1.1 . OUTPUT_FILE ${VLCQT_PLUGIN_QML_NAME}/${VLCQT_PLUGIN_QML_NAME}.qmltypes WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/qml)")
    ENDIF()
ENDIF()
