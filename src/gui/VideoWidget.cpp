/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
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

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "gui/VideoWidget.h"

VlcVideoWidget::VlcVideoWidget(VlcMediaPlayer *player,
                               QWidget *parent)
    : QWidget(parent),
      _vlcVideo(player->video()),
      _hide(true),
      _currentRatio(""),
      _currentCrop(""),
      _currentFilter("")
{
    setMouseTracking(true);

    _widget = new QWidget(this);
    _widget->setMouseTracking(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_widget);
    setLayout(layout);

    _timerMouse = new QTimer(this);
    connect(_timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
    _timerSettings = new QTimer(this);
    connect(_timerSettings, SIGNAL(timeout()), this, SLOT(applyPreviousSettings()));
}

VlcVideoWidget::VlcVideoWidget(QWidget *parent)
    : QWidget(parent),
      _vlcVideo(0),
      _hide(true),
      _currentRatio(""),
      _currentCrop(""),
      _currentFilter("")
{
    setMouseTracking(true);

    _widget = new QWidget(this);
    _widget->setMouseTracking(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_widget);
    setLayout(layout);

    _timerMouse = new QTimer(this);
    connect(_timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
    _timerSettings = new QTimer(this);
    connect(_timerSettings, SIGNAL(timeout()), this, SLOT(applyPreviousSettings()));
}

VlcVideoWidget::~VlcVideoWidget()
{
    delete _timerMouse;
    delete _timerSettings;
    delete _widget;
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
    if(isFullScreen()) {
        emit mouseShow(event->globalPos());
    }

    if(isFullScreen() && _hide) {
        qApp->setOverrideCursor(Qt::ArrowCursor);

        _timerMouse->start(1000);
    }
}
void VlcVideoWidget::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    if(event->button() == Qt::RightButton) {
        qApp->setOverrideCursor(Qt::ArrowCursor);
        emit rightClick(event->globalPos());
    }
}
void VlcVideoWidget::wheelEvent(QWheelEvent *event)
{
    event->ignore();

    if(event->delta() > 0)
        emit wheel(true);
    else
        emit wheel(false);
}

void VlcVideoWidget::hideMouse()
{
    if(isFullScreen() && _hide) {
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

void VlcVideoWidget::setPreviousSettings()
{
    _timerSettings->start(500);
}
void VlcVideoWidget::applyPreviousSettings()
{
    if(_currentRatio.isEmpty() && _currentCrop.isEmpty() && _currentFilter.isEmpty()) {
        _timerSettings->stop();
        return;
    }

    bool ratio = false, crop = false;
    if(_vlcVideo->aspectRatio() != _currentRatio) {
        _vlcVideo->setAspectRatio(_currentRatio);
    } else {
        ratio = true;
    }
    if(_vlcVideo->cropGeometry() != _currentCrop) {
        _vlcVideo->setCropGeometry(_currentCrop);
    } else {
        crop = true;
    }

    _vlcVideo->setDeinterlace(_currentFilter);

    if(ratio && crop)
        _timerSettings->stop();
}

// Aspect ratios
void VlcVideoWidget::setRatioOriginal()
{
    _currentRatio = "";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio1_1()
{
    _currentRatio = "1:1";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio4_3()
{
    _currentRatio = "4:3";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio16_9()
{
    _currentRatio = "16:9";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio16_10()
{
    _currentRatio = "16:10";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio2_21_1()
{
    _currentRatio = "221:100";
    _vlcVideo->setAspectRatio(_currentRatio);
}
void VlcVideoWidget::setRatio5_4()
{
    _currentRatio = "5:4";
    _vlcVideo->setAspectRatio(_currentRatio);
}

// Crop geometries
void VlcVideoWidget::setCropOriginal()
{
    _currentCrop = "";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop16_9()
{
    _currentCrop = "16:9";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop16_10()
{
    _currentCrop = "16:10";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop1_85_1()
{
    _currentCrop = "185:100";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop2_21_1()
{
    _currentCrop = "221:100";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop2_35_1()
{
    _currentCrop = "235:100";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop2_39_1()
{
    _currentCrop = "239:100";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop5_4()
{
    _currentCrop = "5:4";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop5_3()
{
    _currentCrop = "5:3";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop4_3()
{
    _currentCrop = "4:3";
    _vlcVideo->setCropGeometry(_currentCrop);
}
void VlcVideoWidget::setCrop1_1()
{
    _currentCrop = "1:1";
    _vlcVideo->setCropGeometry(_currentCrop);
}

// Deinterlace filters
void VlcVideoWidget::setFilterDisabled()
{
    _currentFilter = "";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterDiscard()
{
    _currentFilter = "discard";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterBlend()
{
    _currentFilter = "blend";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterMean()
{
    _currentFilter = "mean";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterBob()
{
    _currentFilter = "bob";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterLinear()
{
    _currentFilter = "linear";
    _vlcVideo->setDeinterlace(_currentFilter);
}
void VlcVideoWidget::setFilterX()
{
    _currentFilter = "x";
    _vlcVideo->setDeinterlace(_currentFilter);
}
