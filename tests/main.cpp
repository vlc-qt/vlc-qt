/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QApplication>
#else
    #include <QtGui/QApplication>
#endif

#include "core/Common.h"

#if QT_VERSION >= 0x050000
    #include "qml/QmlVideoPlayer.h"
#endif

#include "Tests.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("VLC-Qt Tests");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

#if QT_VERSION >= 0x050000
    VlcQmlVideoPlayer::registerPlugin();
#else
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    QApplication app(argc, argv);
    VlcCommon::setPluginPath(app.applicationDirPath() + "/../plugins");

    Tests mainWindow;
    mainWindow.show();

    return app.exec();
}
