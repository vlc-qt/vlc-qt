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
# List of sources #
###################
SET(TEST_APP_RPATH Test_AppRpath)

# Define the C++ source files
SET(Test_AppRpath_Srcs
    main.cpp
    main.qml
    qml.qrc
)


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${CMAKE_BINARY_DIR}/include
)

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${TEST_APP_RPATH} EXCLUDE_FROM_ALL MACOSX_BUNDLE WIN32 ${Test_AppRpath_Srcs})
ADD_DEPENDENCIES(${TEST_APP_RPATH} ${VLCQT_CORE} ${VLCQT_QML})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(${TEST_APP_RPATH} PROPERTIES INSTALL_RPATH "${QT_LIB_DIR};@executable_path/../Frameworks")

    ADD_CUSTOM_COMMAND(TARGET ${TEST_APP_RPATH}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "Contents/Frameworks/"
        COMMAND ${CMAKE_COMMAND} -E make_directory "Contents/Resources/qml/"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_BINARY_DIR}/src/core/${VLCQT_CORE_NAME}.framework" "Contents/Frameworks/${VLCQT_CORE_NAME}.framework"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_BINARY_DIR}/src/qml/${VLCQT_QML_NAME}.framework" "Contents/Frameworks/${VLCQT_QML_NAME}.framework"
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_BINARY_DIR}/src/plugins/${VLCQT_PLUGIN_QML_NAME}/" "Contents/Resources/qml/${VLCQT_PLUGIN_QML_NAME}"
        COMMAND ${QT_BIN_DIR}/macdeployqt ../${TEST_APP_RPATH}.app -qmldir=${CMAKE_SOURCE_DIR}/tests/app/
        COMMAND open ../${TEST_APP_RPATH}.app
        WORKING_DIRECTORY "${TEST_APP_RPATH}.app"
    )
ENDIF()

# Link the required libraries
TARGET_LINK_LIBRARIES(${TEST_APP_RPATH} Qt5::Quick ${VLCQT_CORE_BINARY} ${VLCQT_QML_BINARY})

IF(STATIC)
    TARGET_LINK_LIBRARIES(${TEST_APP_RPATH} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ENDIF()
