#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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
# OS X Extra #
##############
# Set the OS X Bundle specific CMake variables which will be used to populate the plist for
# the application bundle
SET(MACOSX_BUNDLE_COPYRIGHT "2015 ${PROJECT_AUTHOR}")
SET(MACOSX_BUNDLE_ICON_FILE "${VLCQT_TEST}.icns")
SET(MACOSX_BUNDLE_GUI_IDENTIFIER "si.tano.${PROJECT_NAME}")

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/platform/osx/Info.plist.in
    ${CMAKE_BINARY_DIR}/platform/osx/Info.plist
)

ADD_CUSTOM_TARGET(prepare
    "${CMAKE_SOURCE_DIR}/scripts/osx/vlc_libraries_prepare.sh" "${LIBVLC_BIN_DIR}" "${CMAKE_BINARY_DIR}")

IF(${BUILD_TESTS})
    ADD_CUSTOM_TARGET(dmg
        "${QT_BIN_DIR}/macdeployqt" "${CMAKE_INSTALL_PREFIX}/bin/${VLCQT_TEST}.app" -dmg)
ENDIF()

SET(LIBVLC_PROCESSED_DIR "${CMAKE_BINARY_DIR}/libvlc-processed")
SET(LIBVLC_LIBRARY "${LIBVLC_PROCESSED_DIR}/libvlc.dylib")
SET(LIBVLCCORE_LIBRARY "${LIBVLC_PROCESSED_DIR}/libvlccore.dylib")

FILE(GLOB Vlc_Libs ${LIBVLC_PROCESSED_DIR}/*.dylib)
FILE(GLOB Vlc_Plugins ${LIBVLC_PROCESSED_DIR}/plugins/*.dylib)

IF(Qt5Core_VERSION VERSION_LESS "5.5.0")
    INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_SOURCE_DIR}/scripts/osx/qt_old_postprocess.sh ${VLCQT_CORE_NAME} WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_CORE_NAME}.framework/Versions/${VLCQT_VERSION}/)")
    INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_SOURCE_DIR}/scripts/osx/qt_old_postprocess.sh ${VLCQT_WIDGETS_NAME} WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_WIDGETS_NAME}.framework/Versions/${VLCQT_VERSION}/)")
    INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_SOURCE_DIR}/scripts/osx/qt_old_postprocess.sh ${VLCQT_QML_NAME} WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_QML_NAME}.framework/Versions/${VLCQT_VERSION}/)")
ENDIF()
