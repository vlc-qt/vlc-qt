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

STRING(REGEX REPLACE "bin" "plugins" QT_PLUGINS_DIR "${QT_BIN_DIR}")

SET(Qt4_Libs
    ${QT_BIN_DIR}/QtCore${LE}4.dll
    ${QT_BIN_DIR}/QtGui${LE}4.dll
)

SET(Qt5_Platforms
    ${QT_PLUGINS_DIR}/platforms/qminimal${LE}.dll
    ${QT_PLUGINS_DIR}/platforms/qwindows${LE}.dll
)

SET(Qt5_Libs
    ${QT_BIN_DIR}/Qt5Core${LE}.dll
    ${QT_BIN_DIR}/Qt5Gui${LE}.dll
)

FILE(GLOB Qt5_Libs_Icu ${QT_BIN_DIR}/icu*.dll)

SET(Qt5_Libs_Gles
    ${QT_BIN_DIR}/libEGL${LE}.dll
    ${QT_BIN_DIR}/libGLESv2${LE}.dll
)

FILE(GLOB Qt5_Libs_D3D ${QT_BIN_DIR}/D3DCompiler_*.dll)

SET(Qt5_Libs_Widgets
    ${QT_BIN_DIR}/Qt5Widgets${LE}.dll
)

SET(Qt5_Libs_Qml
    ${QT_BIN_DIR}/Qt5Network${LE}.dll
    ${QT_BIN_DIR}/Qt5Qml${LE}.dll
    ${QT_BIN_DIR}/Qt5Quick${LE}.dll
)

SET(Vlc_Libs
    ${LIBVLC_BIN_DIR}/libvlc.dll
    ${LIBVLC_BIN_DIR}/libvlccore.dll
)

FILE(GLOB Vlc_Gcc "${LIBVLC_BIN_DIR}/libgcc_s_*-1.dll")
IF(Vlc_Gcc)
    SET(Extra_Libs
        ${Vlc_Gcc}
        ${LIBVLC_BIN_DIR}/libstdc++-6.dll
        ${LIBVLC_BIN_DIR}/libwinpthread-1.dll
    )
ENDIF()

IF(MINGW)
    SET(Extra_Libs
        ${Extra_Libs}
        ${QT_BIN_DIR}/libgcc_s_${GCC_EH_METHOD}-1.dll
        ${QT_BIN_DIR}/libstdc++-6.dll
        ${QT_BIN_DIR}/libwinpthread-1.dll
    )
ENDIF()


################
# Installation #
################
IF(QT_VERSION MATCHES 4)
    INSTALL(FILES ${Qt4_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
ELSE()
    INSTALL(FILES ${Qt5_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    INSTALL(FILES ${Qt5_Libs_Icu} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    INSTALL(FILES ${Qt5_Platforms} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/platforms")
    IF(WITH_WIDGETS OR WITH_QML)
        IF(WITH_GLES)
            INSTALL(FILES ${Qt5_Libs_Gles} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
        ENDIF()
        IF(WITH_ANGLE)
            INSTALL(FILES ${Qt5_Libs_D3D} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
        ENDIF()
    ENDIF()
    IF(WITH_WIDGETS)
        INSTALL(FILES ${Qt5_Libs_Widgets} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF()
    IF(WITH_QML)
        INSTALL(FILES ${Qt5_Libs_Qml} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF()
ENDIF()

INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

IF(MINGW OR Vlc_Gcc)
    INSTALL(FILES ${Extra_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
ENDIF()

VLC_INSTALL_PLUGINS(${Vlc_Plugins_Type})
