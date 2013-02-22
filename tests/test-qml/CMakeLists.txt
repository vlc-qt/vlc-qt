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

PROJECT(test-vlcqt-qml)

###################
# List of sources #
###################
# Define the C++ source files
SET(Test_QML_Srcs
    main.cpp
)


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_BINARY_DIR}/tests/test-qml
)

INCLUDE_DIRECTORIES(
    ${LIBVLC_INCLUDE_DIR}
    ${LIBVLC_INCLUDE_DIR}/vlc/plugins
)


# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${PROJECT_NAME} ${Test_QML_Srcs})

# Link the required libraries
IF(QT5)
    QT5_USE_MODULES(${PROJECT_NAME} Quick)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VLCQT_QML_BINARY} ${VLCQT_BINARY})
ELSE(QT5)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${VLCQT_QML_BINARY} ${VLCQT_BINARY})
ENDIF(QT5)


################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
