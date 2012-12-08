#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

PROJECT(test-vlcqt-core)

###################
# List of sources #
###################
# Define the C++ source files
SET(Test_Core_Srcs
    main.cpp
)


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_BINARY_DIR}/tests/test-core
)

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${PROJECT_NAME} ${Test_Core_Srcs})

# Link the required libraries
IF(WITH_QT5)
    QT5_USE_MODULES(${PROJECT_NAME} Core)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VLCQT_BINARY})
ELSE(WITH_QT5)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${VLCQT_BINARY})
ENDIF(WITH_QT5)

################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
