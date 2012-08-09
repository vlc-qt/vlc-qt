/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QCoreApplication>
#include <QtCore/QTextCodec>

#if defined(Qt5)
    #include <QtWidgets/QApplication>
#elif defined(Qt4)
    #include <QtGui/QApplication>
#endif

#include "TestMain.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Test Widgets");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

#if defined(Qt4)
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    QApplication app(argc, argv);

    TestMain mainWindow;
    mainWindow.show();

    return app.exec();
}
