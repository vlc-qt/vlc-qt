/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#include <QtCore/QTextCodec>

#if QT_VERSION >= 0x050000
    #include <QtGui/QGuiApplication>
    #include <QtQuick/QQuickView>
#else
    #include <QtGui/QApplication>
    #include <QtDeclarative/QDeclarativeView>
#endif

#if QT_VERSION >= 0x050000
    #include "qml/QmlVideoPlayer5.h"
#else
    #include "qml/QmlVideoPlayer4.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Test QML");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

#if QT_VERSION < 0x050000
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

    qmlRegisterType<VlcQmlVideoPlayer>("VLCQt", 0, 9, "VlcVideoPlayer");


#if QT_VERSION >= 0x050000
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qt5/video.qml"));
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.show();
#else
    QApplication app(argc, argv);

    QDeclarativeView view;
    view.setSource(QUrl("qt4/video.qml"));
    view.setResizeMode(QDeclarativeView::SizeViewToRootObject);
    view.show();
#endif

    return app.exec();
}

