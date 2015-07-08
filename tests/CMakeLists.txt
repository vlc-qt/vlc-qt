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
IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/platform/windows/tests.rc.in
        ${CMAKE_BINARY_DIR}/platform/windows/tests.rc
    )
ENDIF()

###################
# List of sources #
###################
# Define the UI source files
SET(Test_UIs
    Tests.ui
    common/MetaManager.ui
    common/Recorder.ui
    common/dual/Dual.ui
    widgets/Player.ui
)

# Define the resource files
SET(Test_Resources
    ../resources/logo.qrc
)

# Define the C++ source files
SET(Test_Srcs
    main.cpp
    Tests.cpp
    common/MetaManager.cpp
    common/Recorder.cpp
    common/dual/DualInstance.cpp
    common/dual/DualPlayer.cpp
    widgets/Player.cpp
)

IF(QT_VERSION MATCHES 5)
    SET(Test_Resources
        ${Test_Resources}

        qml/qml.qrc
    )
ENDIF()

IF(${LIBVLC_VERSION} EQUAL 0x020200 OR ${LIBVLC_VERSION} GREATER 0x020200)
    SET(Test_UIs
        ${Test_UIs}

        widgets/EqualizerDialog.ui
    )

    SET(Test_Srcs
        ${Test_Srcs}

        widgets/EqualizerDialog.cpp
    )
ENDIF()


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_SOURCE_DIR}/src/widgets
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/tests
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(Test_Iconset ${CMAKE_SOURCE_DIR}/platform/osx/Project.iconset)

    FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests/${VLCQT_TEST}.app/Contents/Resources)
    FIND_PROGRAM(ICONUTIL_EXECUTABLE NAMES iconutil)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/tests/${VLCQT_TEST}.app/Contents/Resources/${VLCQT_TEST}.icns
        COMMAND ${ICONUTIL_EXECUTABLE} --convert icns --output ${CMAKE_BINARY_DIR}/tests/${VLCQT_TEST}.app/Contents/Resources/${VLCQT_TEST}.icns
        ${Test_Iconset}
    )
    SET(Test_Srcs ${Test_Srcs} ${CMAKE_BINARY_DIR}/tests/${VLCQT_TEST}.app/Contents/Resources/${VLCQT_TEST}.icns)
ENDIF()

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/platform/windows/tests.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/platform/windows/tests.rc
        -o ${CMAKE_BINARY_DIR}/platform/windows/tests.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/platform/windows"
    )
    SET(Test_Srcs ${Test_Srcs} ${CMAKE_BINARY_DIR}/platform/windows/tests.obj)
ENDIF()

IF(MSVC)
    SET(Test_Srcs ${Test_Srcs} ${CMAKE_BINARY_DIR}/platform/windows/tests.rc)
ENDIF()

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${VLCQT_TEST} MACOSX_BUNDLE WIN32 ${Test_UIs} ${Test_Resources} ${Test_Srcs})
ADD_DEPENDENCIES(${VLCQT_TEST} ${VLCQT_CORE} ${VLCQT_WIDGETS})
IF(QT_VERSION MATCHES 5)
    ADD_DEPENDENCIES(${VLCQT_TEST} ${VLCQT_QML})
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(${VLCQT_TEST} PROPERTIES INSTALL_RPATH "${QT_LIB_DIR};@executable_path/../Frameworks")
    SET_TARGET_PROPERTIES(${VLCQT_TEST} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_BINARY_DIR}/platform/osx/Info.plist")
ENDIF()

# Link the required libraries
IF(QT_VERSION MATCHES 4)
    TARGET_LINK_LIBRARIES(${VLCQT_TEST} Qt4::QtGui ${VLCQT_CORE_BINARY} ${VLCQT_WIDGETS_BINARY})
ELSE()
    TARGET_LINK_LIBRARIES(${VLCQT_TEST} Qt5::Quick Qt5::Widgets ${VLCQT_CORE_BINARY} ${VLCQT_QML_BINARY} ${VLCQT_WIDGETS_BINARY})
ENDIF()

IF(STATIC)
    TARGET_LINK_LIBRARIES(${VLCQT_TEST} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ENDIF()


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_TEST}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE DESTINATION .
)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    INSTALL(DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_CORE}.framework/
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${VLCQT_TEST}.app/Contents/Frameworks/${VLCQT_CORE}.framework)
    INSTALL(DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_QML}.framework/
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${VLCQT_TEST}.app/Contents/Frameworks/${VLCQT_QML}.framework)
    INSTALL(DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib/${VLCQT_WIDGETS}.framework/
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${VLCQT_TEST}.app/Contents/Frameworks/${VLCQT_WIDGETS}.framework)
ENDIF()
