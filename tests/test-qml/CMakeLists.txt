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

PROJECT(test-vlcqt-qml)

###################
# List of sources #
###################
# Define the MOC source files
SET(Test_QML_MOCs
    qmlapplicationviewer/qmlapplicationviewer.h
)

# Define the C++ source files
SET(Test_QML_Srcs
    main.cpp

    qmlapplicationviewer/qmlapplicationviewer.cpp
)


################
# Qt settings #
################
# This scripts run the user interface compiler uic and the meta object compiler moc.
IF(WITH_QT5)
    QT5_WRAP_CPP(Test_QML_MOC_Srcs ${Test_QML_MOCs})
ELSE(WITH_QT5)
    QT4_WRAP_CPP(Test_QML_MOC_Srcs ${Test_QML_MOCs})
ENDIF(WITH_QT5)


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/qml
    ${CMAKE_BINARY_DIR}/tests/test-qml
)

# This line adds the include path of the Qt
# directory to the compiler include path
IF(WITH_QT5)
    INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
ELSE(WITH_QT5)
    SET(QT_USE_QTDECLARATIVE True)
    INCLUDE(${QT_USE_FILE})
ENDIF(WITH_QT5)

# This line sets the required Qt libraries
IF(WITH_QT5)
    SET(VLCQT_QTLIB ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})
ELSE(WITH_QT5)
    SET(VLCQT_QTLIB ${QT_LIBRARIES})
ENDIF(WITH_QT5)

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${PROJECT_NAME} ${Test_QML_Srcs} ${Test_QML_MOC_Srcs})

# Here the needed Libraries are added to the link command.
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${VLCQT_QTLIB} ${VLCQT_BINARY})


################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
