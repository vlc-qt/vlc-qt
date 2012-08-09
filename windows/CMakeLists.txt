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
# Windows Extra #
#################
SET(Vlc_Plugins_Type
    3dnow
    access
    access_output
    audio_filter
    audio_mixer
    audio_output
    codec
    control
    demux
    media_library
    meta_engine
    misc
    mmx
    mmxext
    mux
    notify
    packetizer
    services_discovery
    sse2
    stream_filter
    stream_out
    text_renderer
    video_chroma
    video_filter
    video_output
    visualization
)

MACRO(VLC_INSTALL_PLUGINS)
    FOREACH(type ${ARGN})
        FILE(GLOB Vlc_Plugins ${LIBVLC_BIN_DIR}/plugins/${type}/*.dll)
        INSTALL(FILES ${Vlc_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/plugins/${type}")
    ENDFOREACH(type)
ENDMACRO(VLC_INSTALL_PLUGINS)

IF(MINGW)
    STRING(REGEX REPLACE "\\\\" "/" LIBVLC_INCLUDE_DIR "${LIBVLC_INCLUDE_DIR}")

    STRING(REGEX REPLACE "sdk/include" "" LIBVLC_BIN_DIR "${LIBVLC_INCLUDE_DIR}")
    STRING(REGEX REPLACE "include" "bin" LIBVLC_BIN_DIR "${LIBVLC_BIN_DIR}")

    SET(Qt_Libs
        ${QT_BIN_DIR}/QtCore4.dll
        ${QT_BIN_DIR}/QtGui4.dll
    )
    SET(Qt_Libs_QML
        ${QT_BIN_DIR}/QtDeclarative4.dll
        ${QT_BIN_DIR}/QtNetwork4.dll
        ${QT_BIN_DIR}/QtScript4.dll
        ${QT_BIN_DIR}/QtSql4.dll
        ${QT_BIN_DIR}/QtXmlPatterns4.dll
    )
    SET(Vlc_Libs
        ${LIBVLC_BIN_DIR}/libvlc.dll
        ${LIBVLC_BIN_DIR}/libvlccore.dll
    )
ENDIF(MINGW)


################
# Installation #
################
IF(MINGW)
    INSTALL(FILES ${Qt_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    IF(WITH_QML)
        INSTALL(FILES ${Qt_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF(WITH_QML)
    INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    VLC_INSTALL_PLUGINS(${Vlc_Plugins_Type})
ENDIF(MINGW)
