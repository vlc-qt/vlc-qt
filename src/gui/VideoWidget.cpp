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

#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>

#if defined(Qt5)
    #include <QtWidgets/QApplication>
    #include <QtWidgets/QDesktopWidget>
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QToolBar>
#elif defined(Qt4)
    #include <QtGui/QApplication>
    #include <QtGui/QDesktopWidget>
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QToolBar>
#endif

#if defined(Q_OS_MAC)
    #import <Cocoa/Cocoa.h>
#elif defined(Q_WS_X11)
    #include <X11/Xlib.h>
    #include <qx11info_x11.h>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "gui/VideoWidget.h"

VlcVideoWidget::VlcVideoWidget(VlcMediaPlayer *player,
                               QWidget *parent)
    :
#if defined(Q_OS_MAC)
      QMacCocoaViewContainer(0, parent)
#else
      QFrame(parent)
#endif
{
    _vlcMediaPlayer = player;

    connect(_vlcMediaPlayer, SIGNAL(vout(int)), this, SLOT(applyPreviousSettings()));

    initVideoWidget();
}

VlcVideoWidget::VlcVideoWidget(QWidget *parent)
    :
#if defined(Q_OS_MAC)
      QMacCocoaViewContainer(0, parent),
#else
      QFrame(parent),
#endif
      _vlcMediaPlayer(0)
{
    initVideoWidget();
}

VlcVideoWidget::~VlcVideoWidget()
{
    release();

    delete _timerMouse;

#if !defined(Q_OS_MAC)
    delete _layout;

    /* Ensure we are not leaking the video output. This would crash. */
    Q_ASSERT(!_video);
#endif
}

void VlcVideoWidget::initVideoWidget()
{
    setMouseTracking(true);

    _hide = true;
    _enableSettings = false;
    _defaultAspectRatio = Vlc::Original;
    _defaultCropRatio = Vlc::Original;
    _defaultDeinterlacing = Vlc::Disabled;
    _defaultScale = Vlc::NoScale;
    _currentAspectRatio = Vlc::Original;
    _currentCropRatio = Vlc::Original;
    _currentDeinterlacing = Vlc::Disabled;
    _currentScale = Vlc::NoScale;

#if defined(Q_OS_MAC)
    NSView *video = [[NSView alloc] init];
    setCocoaView(video);
    [video release];
#else
    _layout = new QHBoxLayout(this);
    _layout->setContentsMargins(0, 0, 0, 0);
    _video = 0;

    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    setPalette(plt);
#endif

    _timerMouse = new QTimer(this);
    connect(_timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
}

void VlcVideoWidget::setMediaPlayer(VlcMediaPlayer *player)
{
    _vlcMediaPlayer = player;

    connect(_vlcMediaPlayer, SIGNAL(vout(int)), this, SLOT(applyPreviousSettings()));
}

//Events:
void VlcVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->ignore();
    emit fullscreen();
}

void VlcVideoWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
    if (isFullScreen()) {
        emit mouseShow(event->globalPos());
    }

    if (isFullScreen() && _hide) {
        qApp->restoreOverrideCursor();

        _timerMouse->start(1000);
    }
}

void VlcVideoWidget::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    if (event->button() == Qt::RightButton) {
        qApp->restoreOverrideCursor();
        emit rightClick(event->globalPos());
    }
}

void VlcVideoWidget::wheelEvent(QWheelEvent *event)
{
    event->ignore();

    if (event->delta() > 0)
        emit wheel(true);
    else
        emit wheel(false);
}

void VlcVideoWidget::hideMouse()
{
    if (isFullScreen() && _hide) {
        qApp->setOverrideCursor(Qt::BlankCursor);
        _timerMouse->stop();
        emit mouseHide();
    }
}

void VlcVideoWidget::toggleFullscreen()
{
    Qt::WindowFlags flags = windowFlags();
    if (!isFullScreen()) {
        flags |= Qt::Window;
        flags ^= Qt::SubWindow;
        setWindowFlags(flags);
#if defined(Q_WS_X11)
        // This works around a bug with Compiz
        // as the window must be visible before we can set the state
        show();
        raise();
        setWindowState( windowState() | Qt::WindowFullScreen );
#else
        setWindowState( windowState() | Qt::WindowFullScreen );
        show();
#endif
    } else if (isFullScreen()) {
        flags ^= (Qt::Window | Qt::SubWindow);
        setWindowFlags(flags);
        setWindowState( windowState() ^ Qt::WindowFullScreen );
        qApp->restoreOverrideCursor();
        show();
    }
}

void VlcVideoWidget::setCurrentAspectRatio(const Vlc::Ratio &ratio)
{
    _currentAspectRatio = ratio;
}

void VlcVideoWidget::setCurrentCropRatio(const Vlc::Ratio &ratio)
{
    _currentCropRatio = ratio;
}

void VlcVideoWidget::setCurrentDeinterlacing(const Vlc::Deinterlacing &deinterlacing)
{
    _currentDeinterlacing = deinterlacing;
}

void VlcVideoWidget::setCurrentScale(const Vlc::Scale &scale)
{
    _currentScale = scale;
}

void VlcVideoWidget::setDefaultAspectRatio(const Vlc::Ratio &ratio)
{
    _defaultAspectRatio = ratio;
}

void VlcVideoWidget::setDefaultCropRatio(const Vlc::Ratio &ratio)
{
    _defaultCropRatio = ratio;
}

void VlcVideoWidget::setDefaultDeinterlacing(const Vlc::Deinterlacing &deinterlacing)
{
    _defaultDeinterlacing = deinterlacing;
}

void VlcVideoWidget::setDefaultScale(const Vlc::Scale &scale)
{
    _defaultScale = scale;
}

void VlcVideoWidget::enableDefaultSettings()
{
    initDefaultSettings();

    enablePreviousSettings();
}

void VlcVideoWidget::enablePreviousSettings()
{
    _enableSettings = true;
}

void VlcVideoWidget::initDefaultSettings()
{
    _currentAspectRatio = defaultAspectRatio();
    _currentCropRatio = defaultCropRatio();
    _currentDeinterlacing = defaultDeinterlacing();
    _currentScale = defaultScale();
}

void VlcVideoWidget::applyPreviousSettings()
{
    if (!_enableSettings)
        return;

    if (!_vlcMediaPlayer)
        return;

    _vlcMediaPlayer->video()->setAspectRatio(_currentAspectRatio);
    _vlcMediaPlayer->video()->setCropGeometry(_currentCropRatio);
    _vlcMediaPlayer->video()->setScale(_currentScale);
    _vlcMediaPlayer->video()->setDeinterlace(_currentDeinterlacing);

    _enableSettings = false;
}

void VlcVideoWidget::setAspectRatio(const Vlc::Ratio &ratio)
{
    if (_vlcMediaPlayer) {
        _currentAspectRatio = ratio;
        _vlcMediaPlayer->video()->setAspectRatio(ratio);
    }
}

void VlcVideoWidget::setCropRatio(const Vlc::Ratio &ratio)
{
    if (_vlcMediaPlayer) {
        _currentCropRatio = ratio;
        _vlcMediaPlayer->video()->setCropGeometry(ratio);
    }
}

void VlcVideoWidget::setDeinterlacing(const Vlc::Deinterlacing &deinterlacing)
{
    if (_vlcMediaPlayer) {
        _currentDeinterlacing = deinterlacing;
        _vlcMediaPlayer->video()->setDeinterlace(deinterlacing);
    }
}

void VlcVideoWidget::setScale(const Vlc::Scale &scale)
{
    if (_vlcMediaPlayer) {
        _currentScale = scale;
        _vlcMediaPlayer->video()->setScale(scale);
    }
}

void VlcVideoWidget::sync()
{
#if defined(Q_WS_X11)
    /* Make sure the X server has processed all requests.
     * This protects other threads using distinct connections from getting
     * the video widget window in an inconsistent states. */
    XSync(QX11Info::display(), False);
#endif
}

WId VlcVideoWidget::request()
{
#if defined(Q_OS_MAC)
    return WId(cocoaView());
#endif

    if (_video)
        return 0;

    _video = new QWidget();
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    _video->setPalette(plt);
    _video->setAutoFillBackground(true);
    _video->setMouseTracking(true);
    /* Indicates that the widget wants to draw directly onto the screen.
       Widgets with this attribute set do not participate in composition
       management */
    /* This is currently disabled on X11 as it does not seem to improve
     * performance, but causes the video widget to be transparent... */
#ifndef Q_WS_X11
    _video->setAttribute( Qt::WA_PaintOnScreen, true );
#endif

    _layout->addWidget(_video);

    sync();
    return _video->winId();
}

void VlcVideoWidget::release()
{
    if (_video) {
        _layout->removeWidget(_video);
        _video->deleteLater();
        _video = NULL;
    }

    updateGeometry();
}
