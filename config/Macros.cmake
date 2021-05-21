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

MACRO(SYMLINK_FRAMEWORK_TEST Target Path Framework)
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        FILE(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/src/lib")
        ADD_CUSTOM_COMMAND(TARGET ${Target}
            PRE_LINK
            COMMAND "${CMAKE_COMMAND}" -E create_symlink "${CMAKE_BINARY_DIR}/src/${Path}/${Framework}.framework" "${Framework}.framework"
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src/lib"
        )
    ENDIF()
ENDMACRO()

MACRO(GENERATE_PKGCONFIG LibraryName LibraryFolder)
    CONFIGURE_FILE(
        lib${LibraryName}.pc.in
        lib${LibraryName}.pc
        @ONLY
    )

    IF(PKGCONFIG)
        INSTALL(FILES ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/lib${LibraryName}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
    ENDIF()
ENDMACRO()

MACRO(GENERATE_WINDOWS_RC LibraryName LibraryFolder LibrarySrcs)
    CONFIGURE_FILE(
        ${LibraryName}.rc.in
        ${LibraryName}.rc
    )
    # Compile resources with windres
    IF(MINGW)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj
            COMMAND ${CMAKE_RC_COMPILER}
            -i ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.rc
            -o ${CMAKE_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj
            WORKING_DIRECTORY "${VLCQt_ROOT_DIR}/src/${LibraryFolder}"
        )
        #LIST(APPEND ${LibrarySrcs} ${CMAKE_CURRENT_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.obj)
        LIST(APPEND ${LibrarySrcs} ${CURRENT_BINARY_DIR}/${LibraryName}.obj)
    ENDIF()

    IF(MSVC)
        #LIST(APPEND ${LibrarySrcs} ${CMAKE_CURRENT_BINARY_DIR}/src/${LibraryFolder}/${LibraryName}.rc)
        LIST(APPEND ${LibrarySrcs} ${CURRENT_BINARY_DIR}/${LibraryName}.rc)
    ENDIF()
ENDMACRO()
