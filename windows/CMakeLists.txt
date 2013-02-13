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
    ${QT_BIN_DIR}/QtCore4.dll
    ${QT_BIN_DIR}/QtGui4.dll
)

SET(Qt5_Platforms
    ${QT_PLUGINS_DIR}/platforms/qminimal.dll
    ${QT_PLUGINS_DIR}/platforms/qwindows.dll
)

SET(Qt5_Libs
    ${QT_BIN_DIR}/Qt5Core.dll
    ${QT_BIN_DIR}/Qt5Gui.dll
    ${QT_BIN_DIR}/icudt49.dll
    ${QT_BIN_DIR}/icuin49.dll
    ${QT_BIN_DIR}/icuuc49.dll
)

SET(Qt5_Libs_Widgets
    ${QT_BIN_DIR}/Qt5Widgets.dll
    ${QT_BIN_DIR}/libEGL.dll
    ${QT_BIN_DIR}/libGLESv2.dll
    ${QT_BIN_DIR}/D3DCompiler_43.dll
)

SET(Qt4_Libs_Qml
    ${QT_BIN_DIR}/QtDeclarative4.dll
    ${QT_BIN_DIR}/QtNetwork4.dll
    ${QT_BIN_DIR}/QtScript4.dll
    ${QT_BIN_DIR}/QtSql4.dll
    ${QT_BIN_DIR}/QtXmlPatterns4.dll
)

SET(Qt5_Libs_Qml

)

SET(Vlc_Libs
    ${LIBVLC_BIN_DIR}/libvlc.dll
    ${LIBVLC_BIN_DIR}/libvlccore.dll
)

IF(MINGW)
    SET(Extra_Libs
        ${QT_BIN_DIR}/zlib1.dll
    )
ENDIF(MINGW)


################
# Installation #
################
IF(QT5)
    INSTALL(FILES ${Qt5_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    INSTALL(FILES ${Qt5_Platforms} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/platforms")
    IF(WITH_WIDGETS)
        INSTALL(FILES ${Qt5_Libs_Widgets} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF(WITH_WIDGETS)
    IF(WITH_QML)
        INSTALL(FILES ${Qt5_Libs_Qml} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF(WITH_QML)
ELSE(QT5)
    INSTALL(FILES ${Qt4_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    IF(WITH_QML)
        INSTALL(FILES ${Q4t_Libs_Qml} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
    ENDIF(WITH_QML)
ENDIF(QT5)

INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

IF(MINGW)
    INSTALL(FILES ${Extra_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
ENDIF(MINGW)

VLC_INSTALL_PLUGINS(${Vlc_Plugins_Type})
