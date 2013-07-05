#############################################################################
# Tano - An Open IP TV Player
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>./
#############################################################################
# OS X Extra #
##############
STRING(REGEX REPLACE "sdk/include" "" LIBVLC_BIN_DIR "${LIBVLC_INCLUDE_DIR}")
STRING(REGEX REPLACE "include" "plugins" LIBVLC_PLUGINS_DIR "${LIBVLC_BIN_DIR}")
STRING(REGEX REPLACE "include" "lib" LIBVLC_LIB_DIR "${LIBVLC_BIN_DIR}")

SET(Vlc_Libs
    ${LIBVLC_LIB_DIR}/libvlc.dylib
    ${LIBVLC_LIB_DIR}/libvlc.5.dylib
    ${LIBVLC_LIB_DIR}/libvlccore.dylib
    ${LIBVLC_LIB_DIR}/libvlccore.5.dylib
)

FILE(GLOB Vlc_Plugins ${LIBVLC_PLUGINS_DIR}/*.dylib)


################
# Installation #
################
INSTALL(FILES ${Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")

INSTALL(FILES ${Vlc_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/plugins")
