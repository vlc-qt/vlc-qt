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
ADD_DEFINITIONS(-DVLCQT_CORE_LIBRARY)

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF()


###################
# List of sources #
###################
# Deprecated C++ source files
SET(VLCQT_CORE_SRCS_DEPRECATED
    VideoFrame.cpp
    VideoMemoryStream.cpp
)
IF(NOT MSVC)
    SET_SOURCE_FILES_PROPERTIES (${VLCQT_CORE_SRCS_DEPRECATED} PROPERTIES COMPILE_FLAGS -Wno-deprecated)
ENDIF()

# Define the C++ source files
SET(VLCQT_CORE_SRCS
    AbstractVideoStream.cpp
    Audio.cpp
    Common.cpp
    Enums.cpp
    Error.cpp
    Instance.cpp
    Media.cpp
    MediaList.cpp
    MediaListPlayer.cpp
    MediaPlayer.cpp
    MetaManager.cpp
    ModuleDescription.cpp
    SharedExportCore.h
    Stats.h
    TrackModel.cpp
    Video.cpp
    VideoDelegate.h
    VideoFrameYUV.cpp
    VideoStream.cpp

    ${VLCQT_CORE_SRCS_DEPRECATED}
)

# Deprecated Include files
SET(VLCQT_CORE_HEADERS_DEPRECATED
    VideoFrame.h
    VideoMemoryStream.h
)

# Define the Include files
SET(VLCQT_CORE_HEADERS
    AbstractVideoStream.h
    Audio.h
    Common.h
    Enums.h
    Error.h
    Instance.h
    Media.h
    MediaList.h
    MediaListPlayer.h
    MediaPlayer.h
    MetaManager.h
    ModuleDescription.h
    SharedExportCore.h
    Stats.h
    TrackModel.h
    Video.h
    VideoDelegate.h
    VideoFrameYUV.h
    VideoStream.h

    ${VLCQT_CORE_HEADERS_DEPRECATED}

    ${CMAKE_BINARY_DIR}/src/Config.h
)

IF(${LIBVLC_VERSION} EQUAL 0x020200 OR ${LIBVLC_VERSION} GREATER 0x020200)
    SET(VLCQT_CORE_SRCS
        ${VLCQT_CORE_SRCS}

        Equalizer.cpp
    )

    SET(VLCQT_CORE_HEADERS
        ${VLCQT_CORE_HEADERS}

        Equalizer.h
    )
ENDIF()

IF(NOT STATIC AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQT_CORE_SRCS
        ${VLCQT_CORE_SRCS}
        ${Vlc_Libs}
        ${Vlc_Plugins}
    )
    SET_SOURCE_FILES_PROPERTIES (
        ${Vlc_Libs}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION lib
    )
    SET_SOURCE_FILES_PROPERTIES (
        ${Vlc_Plugins}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION lib/vlc/plugins
    )
ENDIF()

IF(MSVC OR MINGW)
    SET(VLCQT_CORE_SRCS
        ${VLCQT_CORE_SRCS}
        compat/asprintf.c
        compat/vasprintf.c
    )
ENDIF()


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${LIBVLC_INCLUDE_DIR}
    ${LIBVLC_INCLUDE_DIR}/vlc/plugins
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_BINARY_DIR}/src
)

# Additional macros
GENERATE_PKGCONFIG(${VLCQT_CORE_NAME} core)
GENERATE_WINDOWS_RC(${VLCQT_CORE_NAME} core VLCQT_CORE_SRCS)

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_CORE} STATIC ${VLCQT_CORE_SRCS} ${VLCQT_CORE_HEADERS})
ELSE()
    ADD_LIBRARY(${VLCQT_CORE} SHARED ${VLCQT_CORE_SRCS} ${VLCQT_CORE_HEADERS})
ENDIF()

# Linux/Mac: Set framework, version and headers
SET_TARGET_PROPERTIES(${VLCQT_CORE} PROPERTIES FRAMEWORK ON
                                               OUTPUT_NAME "${VLCQT_CORE_NAME}"
                                               VERSION ${VLCQT_VERSION}
                                               SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                                               PUBLIC_HEADER "${VLCQT_CORE_HEADERS}"
)

# Link the required libraries
IF(QT_VERSION MATCHES 4)
    TARGET_LINK_LIBRARIES(${VLCQT_CORE} PRIVATE Qt4::QtCore)
ELSE()
    TARGET_LINK_LIBRARIES(${VLCQT_CORE} PRIVATE Qt5::Core)
ENDIF()
IF(NOT STATIC)
    TARGET_LINK_LIBRARIES(${VLCQT_CORE} PRIVATE ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ENDIF()

# Provide valid includes for other modules
IF(MINGW OR MSVC)
    FILE(COPY ${VLCQT_CORE_HEADERS} DESTINATION "${CMAKE_BINARY_DIR}/include/${VLCQT_CORE_NAME}")
ELSE()
    FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")
    ADD_CUSTOM_COMMAND(TARGET ${VLCQT_CORE}
        PRE_BUILD
        COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_SOURCE_DIR}/src/core" "include/${VLCQT_CORE_NAME}"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
ENDIF()


################
# Installation #
################
IF(NOT STATIC AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQtCoreIncludesLocation lib/${VLCQT_CORE_NAME}.framework)
    SET(VLCQtCorePublicHeaderLocation lib/${VLCQT_CORE_NAME}.framework)
ELSE()
    SET(VLCQtCoreIncludesLocation include)
    SET(VLCQtCorePublicHeaderLocation include/${VLCQT_CORE_NAME})
ENDIF()

INSTALL(TARGETS ${VLCQT_CORE} EXPORT VLCQtCoreTargets
        RUNTIME DESTINATION bin
        FRAMEWORK DESTINATION lib${LIB_SUFFIX}
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        INCLUDES DESTINATION ${VLCQtCoreIncludesLocation}
        PUBLIC_HEADER DESTINATION ${VLCQtCorePublicHeaderLocation}
)
