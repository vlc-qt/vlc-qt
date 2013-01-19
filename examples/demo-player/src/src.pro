#############################################################################
# VLC-Qt Demo Player
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

TARGET      = demo-player
TEMPLATE    = app

QT          += core gui

SOURCES     += main.cpp\
               DemoPlayer.cpp

HEADERS     += DemoPlayer.h

FORMS       += DemoPlayer.ui

LIBS        += -lvlc-qt -lvlc-qt-widgets

# Edit below for custom library location
#LIBS     += -L/home/tadej/workspace/tanoprojects/install/linux-devel/lib -lvlc-qt -lvlc-qt-widgets
#INCLUDEPATH += /home/tadej/workspace/tanoprojects/install/linux-devel/include
