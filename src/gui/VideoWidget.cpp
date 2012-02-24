/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolBar>

#if defined(Q_WS_MAC)
 #import <Cocoa/Cocoa.h>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "gui/VideoWidget.h"

VlcVideoWidget::VlcVideoWidget(VlcMediaPlayer *player,
                               QWidget *parent)
    :
#if defined(Q_WS_MAC)
      QMacCocoaViewContainer(0, parent),
#else
      QWidget(parent),
#endif
      _vlcVideo(player->video())
{
    initVideoWidget();
}

VlcVideoWidget::VlcVideoWidget(QWidget *parent)
    :
#if defined(Q_WS_MAC)
      QMacCocoaViewContainer(0, parent),
#else
      QWidget(parent),
#endif
      _vlcVideo(0)
{
    initVideoWidget();
}

VlcVideoWidget::~VlcVideoWidget()
{
    delete _timerMouse;
    delete _timerSettings;
    delete _widget;
}

void VlcVideoWidget::initVideoWidget()
{
    setMouseTracking(true);

    _hide = true;
    _defaultAspectRatio = Vlc::Original;
    _defaultCropRatio = Vlc::Original;
    _defaultDeinterlacing = Vlc::Disabled;
    _currentAspectRatio = Vlc::Original;
    _currentCropRatio = Vlc::Original;
    _currentDeinterlacing = Vlc::Disabled;

#if defined(Q_WS_MAC)
    NSView *video = [[NSView alloc] init];
    setCocoaView(video);
    [video release];
#else
    _widget = new QWidget(this);
    _widget->setMouseTracking(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_widget);
    setLayout(layout);
#endif

    _timerMouse = new QTimer(this);
    connect(_timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
    _timerSettings = new QTimer(this);
    connect(_timerSettings, SIGNAL(timeout()), this, SLOT(applyPreviousSettings()));
}

void VlcVideoWidget::setMediaPlayer(VlcMediaPlayer *player)
{
    _vlcVideo = player->video();
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
        qApp->setOverrideCursor(Qt::ArrowCursor);

        _timerMouse->start(1000);
    }
}

void VlcVideoWidget::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    if (event->button() == Qt::RightButton) {
        qApp->setOverrideCursor(Qt::ArrowCursor);
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
#ifdef Q_WS_X11
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
        qApp->setOverrideCursor(Qt::ArrowCursor);
        show();
    }
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

void VlcVideoWidget::enableDefaultSettings()
{
    initDefaultSettings();

    enablePreviousSettings();
}

void VlcVideoWidget::enablePreviousSettings()
{
    _timerSettings->start(500);
}

void VlcVideoWidget::initDefaultSettings()
{
    _currentAspectRatio = defaultAspectRatio();
    _currentCropRatio = defaultCropRatio();
    _currentDeinterlacing = defaultDeinterlacing();
}

void VlcVideoWidget::applyPreviousSettings()
{
    bool ratio = false, crop = false;
    if (_vlcVideo->aspectRatio() != _currentAspectRatio) {
        _vlcVideo->setAspectRatio(_currentAspectRatio);
    } else {
        ratio = true;
    }
    if (_vlcVideo->cropGeometry() != _currentCropRatio) {
        _vlcVideo->setCropGeometry(_currentCropRatio);
    } else {
        crop = true;
    }

    _vlcVideo->setDeinterlace(_currentDeinterlacing);

    if (ratio && crop)
        _timerSettings->stop();
}

void VlcVideoWidget::setAspectRatio(const Vlc::Ratio &ratio)
{
    _currentAspectRatio = ratio;
    _vlcVideo->setAspectRatio(ratio);
}

void VlcVideoWidget::setCropRatio(const Vlc::Ratio &ratio)
{
    _currentCropRatio = ratio;
    _vlcVideo->setCropGeometry(ratio);
}

void VlcVideoWidget::setDeinterlacing(const Vlc::Deinterlacing &deinterlacing)
{
    _currentDeinterlacing = deinterlacing;
    _vlcVideo->setDeinterlace(deinterlacing);
}
