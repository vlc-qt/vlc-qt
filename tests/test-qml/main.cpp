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
#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlContext>

#include "Enums.h"
#include "qml/QmlVideoPlayer.h"

class Viewer: public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(bool isFullscreen READ isFullscreen NOTIFY isFullscreenChanged)
public:
    Viewer( QWindow *parent = 0 ) :
        QQuickView( parent )
    {
        connect( this, &Viewer::windowStateChanged, this, &Viewer::windowStateChanged );

        setTitle( "vlc-qt-qml" );
        qmlRegisterType<Vlc>("VLCQt", 0, 9, "Vlc");
        qmlRegisterType<VlcQmlVideoPlayer>("VLCQt", 0, 9, "VlcVideoPlayer");

        QQmlContext *context = rootContext();
        context->setContextProperty( "viewer", this );

        setResizeMode( QQuickView::SizeRootObjectToView );
        #ifdef Q_OS_MACX
            setFlags( flags() | Qt::WindowFullscreenButtonHint );
        #endif

        setSource( QUrl::fromLocalFile( qApp->applicationDirPath() + "/qml/video.qml" ) );
    }

    Q_INVOKABLE void toggleFullscreen()
    {
        setWindowState( ( Qt::WindowState )( windowState() ^ Qt::WindowFullScreen ) );
    }

    bool isFullscreen()
    {
        return ( Qt::WindowState )( windowState() & Qt::WindowFullScreen );
    }

private slots:
    void windowStateChanged()
    {
        emit isFullscreenChanged();
    }

signals:
    void isFullscreenChanged();
};

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("Test QML");
    QCoreApplication::setAttribute(Qt::AA_X11InitThreads);

    QGuiApplication app(argc, argv);

    Viewer view;
    view.show();

    return app.exec();
}

#include "main.moc"
