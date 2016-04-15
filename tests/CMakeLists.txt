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
# Macros #
##########
SET(TestCommonFiles ${CMAKE_SOURCE_DIR}/tests/common/TestsCommon.cpp)

MACRO(ADD_AUTO_TEST TestName)
    SET(Test_${TestName}_Srcs ${ARGN} ${TestCommonFiles})

    ADD_EXECUTABLE(Test_${TestName} ${Test_${TestName}_Srcs})
    ADD_DEPENDENCIES(Test_${TestName} ${VLCQT_CORE})
    TARGET_LINK_LIBRARIES(Test_${TestName} Qt5::Core Qt5::Test ${VLCQT_CORE})

    IF(${TestName} MATCHES "Qml")
        ADD_DEPENDENCIES(Test_${TestName} ${VLCQT_QML})
        TARGET_LINK_LIBRARIES(Test_${TestName} Qt5::QuickTest)
    ENDIF()

    IF(${TestName} MATCHES "Widgets")
        ADD_DEPENDENCIES(Test_${TestName} ${VLCQT_WIDGETS})
        TARGET_LINK_LIBRARIES(Test_${TestName} Qt5::Widgets ${VLCQT_WIDGETS})
    ENDIF()

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET_TARGET_PROPERTIES(Test_${TestName} PROPERTIES BUILD_WITH_INSTALL_RPATH FALSE)
    ENDIF()

    ADD_TEST(Test_${TestName} Test_${TestName})
    IF(MINGW OR MSVC)
        SET_TESTS_PROPERTIES(Test_${TestName} PROPERTIES ENVIRONMENT "PATH=${WINDOWS_RUN_PATH};QML2_IMPORT_PATH=${CMAKE_BINARY_DIR}/src/plugins")
    ELSE()
        SET_TESTS_PROPERTIES(Test_${TestName} PROPERTIES ENVIRONMENT "QML2_IMPORT_PATH=${CMAKE_BINARY_DIR}/src/plugins")
    ENDIF()
ENDMACRO()


#################
# Configuration #
#################
ADD_DEFINITIONS(-DQUICK_TEST_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}/tests/qml/\")

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/tests/TestsConfig.h.in
    ${CMAKE_BINARY_DIR}/tests/TestsConfig.h
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests/common
    ${CMAKE_BINARY_DIR}/include
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/tests
    ${CMAKE_BINARY_DIR}/tests/core
    ${CMAKE_BINARY_DIR}/tests/qml
    ${CMAKE_BINARY_DIR}/tests/widgets
)

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(qml)
ADD_SUBDIRECTORY(widgets)

ADD_SUBDIRECTORY(app)
