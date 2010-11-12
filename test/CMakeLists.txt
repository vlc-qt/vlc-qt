#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################

PROJECT(test-vlc-qt)

###################
# List of sources #
###################
# Define the UI source files
SET(Test_UIs
	TestMain.ui
	TestMetaManager.ui
)

# Define the MOC source files
SET(Test_MOCs	# List of classes which Qt needs to produce MOCs for them (in order for events, signals, slots and other macros to work
	TestMain.h
	TestMetaManager.h
)

# Define the C++ source files
SET(Test_Srcs
	main.cpp
	TestMain.cpp
	TestMetaManager.cpp
)

################
# Qt4 settings #
################
# This scripts runs the user interface compiler uic.
QT4_WRAP_UI(Test_UIC_Srcs ${Test_UIs})

# This script runs the meta object compiler moc.
QT4_WRAP_CPP(Test_MOC_Srcs ${Test_MOCs})



####################################
# Include paths and set up targets #
####################################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src" "${CMAKE_BINARY_DIR}/test")

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE(${QT_USE_FILE})

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(test-vlc-qt ${Test_UIC_Srcs} ${Test_Srcs} ${Test_MOC_Srcs})

# Here the needed Qt Libraries are added to the link command.
TARGET_LINK_LIBRARIES(test-vlc-qt ${QT_LIBRARIES} ${CMAKE_BINARY_DIR}/src/libvlc-qt.so)
