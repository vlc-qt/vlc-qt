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
    demux
    meta_engine
    misc
    mmx
    mmxext
    mux
    packetizer
    services_discovery
    sse2
    stream_filter
    stream_out
    text_renderer
    video_chroma
    video_filter
    video_output
)

MACRO(VLC_INSTALL_PLUGINS)
    FOREACH(type ${ARGN})
        FILE(GLOB Vlc_Plugins ${LIBVLC_BIN_DIR}/plugins/${type}/*.dll)
        INSTALL(FILES ${Vlc_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/plugins/${type}")
    ENDFOREACH(type)
ENDMACRO(VLC_INSTALL_PLUGINS)

STRING(REGEX REPLACE "\\\\" "/" LIBVLC_INCLUDE_DIR "${LIBVLC_INCLUDE_DIR}")

STRING(REGEX REPLACE "sdk/include" "" LIBVLC_BIN_DIR "${LIBVLC_INCLUDE_DIR}")
STRING(REGEX REPLACE "include" "bin" LIBVLC_BIN_DIR "${LIBVLC_BIN_DIR}")

SET(Vlc_Libs
    ${LIBVLC_BIN_DIR}/libvlc.dll
    ${LIBVLC_BIN_DIR}/libvlccore.dll
)

FILE(GLOB Vlc_Gcc "${LIBVLC_BIN_DIR}/libgcc_s_*-1.dll")
IF(Vlc_Gcc)
    SET(Extra_Libs
        ${Vlc_Gcc}
    )
ENDIF()

FILE(GLOB Vlc_Std "${LIBVLC_BIN_DIR}/libstdc++-6.dll")
IF(Vlc_Std)
    SET(Extra_Libs
        ${LIBVLC_BIN_DIR}/libstdc++-6.dll
        ${LIBVLC_BIN_DIR}/libwinpthread-1.dll
    )
ENDIF()

IF(${BUILD_TESTS})
    ADD_CUSTOM_TARGET(windows
        "${QT_BIN_DIR}/windeployqt.exe" "${CMAKE_INSTALL_PREFIX}/test${LS}/${VLCQT_TEST}.exe")
ENDIF()


################
# Installation #
################
INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
IF(MINGW OR Vlc_Gcc)
    INSTALL(FILES ${Extra_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
ENDIF()

VLC_INSTALL_PLUGINS(${Vlc_Plugins_Type})
