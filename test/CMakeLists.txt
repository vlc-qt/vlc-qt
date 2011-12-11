#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2011 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#############################################################################

PROJECT(test-vlc-qt)

###################
# List of sources #
###################
# Define the UI source files
SET(Test_UIs
    TestDual.ui
    TestMain.ui
    TestMetaManager.ui
    TestPlayer.ui
    TestRecorder.ui
)

# Define the MOC source files
SET(Test_MOCs    # List of classes which Qt needs to produce MOCs for them (in order for events, signals, slots and other macros to work
    TestDualInstance.h
    TestDualPlayer.h
    TestMain.h
    TestMetaManager.h
    TestPlayer.h
    TestRecorder.h
)

# Define the C++ source files
SET(Test_Srcs
    main.cpp
    TestDualInstance.cpp
    TestDualPlayer.cpp
    TestMain.cpp
    TestMetaManager.cpp
    TestPlayer.cpp
    TestRecorder.cpp
)


################
# Qt4 settings #
################
# This scripts runs the user interface compiler uic.
QT4_WRAP_UI(Test_UIC_Srcs ${Test_UIs})

# This script runs the meta object compiler moc.
QT4_WRAP_CPP(Test_MOC_Srcs ${Test_MOCs})


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src" "${CMAKE_BINARY_DIR}/test")
INCLUDE_DIRECTORIES(${LIBVLC_INCLUDE_DIR})

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE(${QT_USE_FILE})

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(test-vlc-qt ${Test_UIC_Srcs} ${Test_Srcs} ${Test_MOC_Srcs})

# Here the needed Qt Libraries are added to the link command.
IF(MINGW)
    TARGET_LINK_LIBRARIES(test-vlc-qt ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY} ${CMAKE_BINARY_DIR}/src/libvlc-qt.dll.a)
ELSE(MINGW)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    TARGET_LINK_LIBRARIES(test-vlc-qt ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY} ${CMAKE_BINARY_DIR}/src/libvlc-qt.dylib)
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    TARGET_LINK_LIBRARIES(test-vlc-qt ${QT_LIBRARIES} ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY} ${CMAKE_BINARY_DIR}/src/libvlc-qt.so)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ENDIF(MINGW)


################
# Installation #
################
INSTALL(TARGETS test-vlc-qt    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
