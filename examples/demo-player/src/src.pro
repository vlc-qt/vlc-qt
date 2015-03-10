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

TARGET      = demo-player
TEMPLATE    = app

QT          += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES     += main.cpp\
               DemoPlayer.cpp

HEADERS     += DemoPlayer.h

FORMS       += DemoPlayer.ui

LIBS        += -lvlc-qt -lvlc-qt-widgets

# Edit below for custom library location
#LIBS     += -L/home/tadej/workspace/tanoprojects/install/linux-devel/lib -lvlc-qt -lvlc-qt-widgets
#INCLUDEPATH += /home/tadej/workspace/tanoprojects/install/linux-devel/include

# Copy required dlls on windows with install target
#win32 {
#	CONFIG(debug, debug|release) {
#		LIBS += -L../../../../vlc-qt-build-debug/install/lib -llibvlc-qt -llibvlc-qt-widgets
#		INCLUDEPATH += ../../../../vlc-qt-build-debug/install/include
#		vlcQtDlls.path = $$OUT_PWD/debug
#		vlcQtDlls.files = ../../../../vlc-qt-build-debug/install/bin/libvlc*
#		vlcQtDlls.files += ../../../../vlc-qt-build-debug/install/bin/plugins
#	} else {
#		LIBS += -L../../../../vlc-qt-build/install/lib -llibvlc-qt -llibvlc-qt-widgets
#		INCLUDEPATH += ../../../../vlc-qt-build/install/include
#		vlcQtDlls.path = $$OUT_PWD/release
#		vlcQtDlls.files = ../../../../vlc-qt-build/install/bin/libvlc*
#		vlcQtDlls.files += ../../../../vlc-qt-build/install/bin/plugins
#	}
#	INSTALLS += vlcQtDlls
#}
