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

MACRO(GENERATE_PKGCONFIG LibraryName LibraryFolder)
    CONFIGURE_FILE(
        lib${LibraryName}.pc.in
        lib${LibraryName}.pc
        @ONLY
    )

    IF(PKGCONFIG)
        INSTALL(FILES ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/lib${LibraryName}.pc DESTINATION lib${LIB_SUFFIX}/pkgconfig)
    ENDIF()
ENDMACRO()

MACRO(GENERATE_WINDOWS_RC LibraryName LibraryFolder LibrarySrcs)
    IF(MINGW OR MSVC)
        CONFIGURE_FILE(
            ${LibraryName}.rc.in
            ${LibraryName}.rc
        )
    ENDIF()

    # Compile resources with windres
    IF(MINGW)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj
            COMMAND ${CMAKE_RC_COMPILER}
            -i ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.rc
            -o ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/${LibraryFolder}"
        )
        LIST(APPEND ${LibrarySrcs} ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj)
    ENDIF()

    IF(MSVC)
        LIST(APPEND ${LibrarySrcs} ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.rc)
    ENDIF()
ENDMACRO()
