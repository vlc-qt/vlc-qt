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
IF(MSVC OR MINGW)
    SET(WINDOWS_TEST_PATH "${LIBVLC_BIN_DIR}\;${QT_BIN_DIR}\;${CMAKE_BINARY_DIR}/src/core\;${CMAKE_BINARY_DIR}/src/qml\;${CMAKE_BINARY_DIR}/src/widgets\;")
    STRING(REGEX REPLACE "/" "\\\\" WINDOWS_TEST_PATH "${WINDOWS_TEST_PATH}")
ENDIF()

SET(TestCommonFiles ${CMAKE_SOURCE_DIR}/tests/common/TestsCommon.cpp)

MACRO(ADD_AUTO_TEST TestName TestSrc)
    SET(Test_${TestName}_Srcs ${TestSrc} ${TestCommonFiles})

    ADD_EXECUTABLE(Test_${TestName} ${Test_${TestName}_Srcs})
    ADD_DEPENDENCIES(Test_${TestName} ${VLCQT_CORE})
    TARGET_LINK_LIBRARIES(Test_${TestName} Qt5::Core Qt5::Test ${VLCQT_CORE_BINARY})

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET_TARGET_PROPERTIES(Test_${TestName} PROPERTIES BUILD_WITH_INSTALL_RPATH FALSE)
    ENDIF()

    ADD_TEST(Test_${TestName} Test_${TestName})
    IF(MINGW OR MSVC)
        SET_TESTS_PROPERTIES(Test_${TestName} PROPERTIES ENVIRONMENT "PATH=${WINDOWS_TEST_PATH}")
    ENDIF()
ENDMACRO()


#################
# Configuration #
#################

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/tests/TestsConfig.h.in
    ${CMAKE_BINARY_DIR}/tests/TestsConfig.h
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests/common
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/tests
    ${CMAKE_BINARY_DIR}/tests/core
)

ADD_SUBDIRECTORY(core)
