#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

MACRO(QT5_FIND_LIBRARY_DIR arg)
    IF(NOT QT_QMAKE_EXECUTABLE)
        FIND_PROGRAM(QT_QMAKE_EXECUTABLE NAMES qmake qmake5 qmake-qt5
                     PATHS "${QT_SEARCH_PATH}/bin" "$ENV{QTDIR}/bin")
        SET(QT_QMAKE_EXECUTABLE ${QT_QMAKE_EXECUTABLE} CACHE PATH "Qt qmake program.")
    ENDIF(NOT QT_QMAKE_EXECUTABLE)

    EXEC_PROGRAM(${QT_QMAKE_EXECUTABLE} ARGS "-query QT_VERSION" OUTPUT_VARIABLE QTVERSION)
    IF(NOT QTVERSION MATCHES "5.*")
        MESSAGE(FATAL_ERROR "CMake was unable to find Qt5, put qmake in your path or set QTDIR/QT_QMAKE_EXECUTABLE.")
    ENDIF(NOT QTVERSION MATCHES "5.*")

    IF(NOT QT_LIBRARY_DIR)
        EXEC_PROGRAM(${QT_QMAKE_EXECUTABLE} ARGS "-query QT_INSTALL_LIBS" OUTPUT_VARIABLE QTLIBS)
        SET(QT_LIBRARY_DIR ${QTLIBS} CACHE INTERNAL "" FORCE)
    ENDIF(NOT QT_LIBRARY_DIR)

    SET(${arg} ${QT_LIBRARY_DIR})
ENDMACRO(QT5_FIND_LIBRARY_DIR)
