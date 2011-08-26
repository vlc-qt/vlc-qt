#############################################################################
# VLC-Qt qmake Demo
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

QT       += core gui

TARGET = demo-qmake
TEMPLATE = app


SOURCES += main.cpp\
        DemoPlayer.cpp

HEADERS  += DemoPlayer.h

FORMS    += DemoPlayer.ui

LIBS     += -L/home/tadej/workspace/install/lib -lvlc-qt # Edit for your configuration

INCLUDEPATH += /home/tadej/workspace/install/include # Edit for your configuration
