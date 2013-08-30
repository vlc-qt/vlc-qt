#############################################################################
# VLC-Qt Demo Player
# Copyright (C) 2013 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# List of sources #
###################
# Define the UI source files
SET(Project_UIs
	DemoPlayer.ui
)

# Define the MOC source files
SET(Project_MOCs
	DemoPlayer.h
)

# Define the C++ source files
SET(Project_Srcs
	main.cpp
	DemoPlayer.cpp
)

################
# Qt4 settings #
################
IF(QT5)
    # This scripts runs the user interface compiler uic.
    QT5_WRAP_UI(Project_UIC_Srcs ${Project_UIs})
    # This script runs the meta object compiler moc.
    QT5_WRAP_CPP(Project_MOC_Srcs ${Project_MOCs})
ELSE(QT5)
    # This scripts runs the user interface compiler uic.
    QT4_WRAP_UI(Project_UIC_Srcs ${Project_UIs})
    # This script runs the meta object compiler moc.
    QT4_WRAP_CPP(Project_MOC_Srcs ${Project_MOCs})
ENDIF(QT5)


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(${LIBVLCQT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
)

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE(${QT_USE_FILE})

# This line tells cmake to create the Project program.
ADD_EXECUTABLE(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${Project_UIC_Srcs} ${Project_Srcs} ${Project_MOC_Srcs})

# Here the needed Qt Libraries are added to the link command.
IF(QT5)
    QT5_USE_MODULES(${PROJECT_NAME} Widgets)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBVLCQT_WIDGETS_LIBRARY} ${LIBVLCQT_LIBRARY})
ELSE(QT5)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES} ${LIBVLCQT_WIDGETS_LIBRARY} ${LIBVLCQT_LIBRARY})
ENDIF(QT5)


################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    BUNDLE DESTINATION .
)
