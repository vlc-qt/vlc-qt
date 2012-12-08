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
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QSlider>
#elif defined(Qt4)
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QLabel>
    #include <QtGui/QSlider>
#endif

#include "core/Audio.h"
#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "widgets/WidgetVolumeSlider.h"

VlcWidgetVolumeSlider::VlcWidgetVolumeSlider(VlcMediaPlayer *player,
                                 QWidget *parent)
    : QWidget(parent),
      _vlcAudio(player->audio()),
      _vlcMediaPlayer(player)
{
    initWidgetVolumeSlider();
}

VlcWidgetVolumeSlider::VlcWidgetVolumeSlider(QWidget *parent)
    : QWidget(parent),
      _vlcAudio(0),
      _vlcMediaPlayer(0)
{
    initWidgetVolumeSlider();
}

VlcWidgetVolumeSlider::~VlcWidgetVolumeSlider()
{
    delete _slider;
    delete _label;
    delete _timer;
}

void VlcWidgetVolumeSlider::initWidgetVolumeSlider()
{
    _lock = false;

    _slider = new QSlider(this);
    _slider->setOrientation(Qt::Horizontal);
    _slider->setMaximum(200);

    _label = new QLabel(this);
    _label->setMinimumWidth(20);
    _label->setText(QString().number(0));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_slider);
    layout->addWidget(_label);
    setLayout(layout);

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateVolume()));
    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
}

void VlcWidgetVolumeSlider::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    lock();
}

void VlcWidgetVolumeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();

    unlock();
}

void VlcWidgetVolumeSlider::setMediaPlayer(VlcMediaPlayer *player)
{
    _vlcAudio = player->audio();
    _vlcMediaPlayer = player;

    _timer->start(100);
}

bool VlcWidgetVolumeSlider::mute() const
{
    if (!(_vlcMediaPlayer->state() == Vlc::Buffering ||
        _vlcMediaPlayer->state() == Vlc::Playing ||
        _vlcMediaPlayer->state() == Vlc::Paused))
        return false;
    else
        return _vlcAudio->getMute();
}

void VlcWidgetVolumeSlider::setMute(const bool &enabled)
{
    if (!(_vlcMediaPlayer->state() == Vlc::Buffering ||
        _vlcMediaPlayer->state() == Vlc::Playing ||
        _vlcMediaPlayer->state() == Vlc::Paused))
        return;

    if (!enabled) {
        _timer->start(100);
        _slider->setDisabled(false);
        _label->setDisabled(false);
    } else {
        _timer->stop();
        _slider->setDisabled(true);
        _label->setDisabled(true);
    }

    _vlcAudio->toggleMute();
}

void VlcWidgetVolumeSlider::setVolume(const int &volume)
{
    if (_currentVolume == volume)
        return;

    lock();

    _currentVolume = volume;
    _slider->setValue(_currentVolume);
    _label->setText(QString().number(_currentVolume));

    emit newVolume(_currentVolume);

    unlock();
}

void VlcWidgetVolumeSlider::updateVolume()
{
    if (_lock)
        return;

    if (!_vlcMediaPlayer)
        return;

    if (_vlcMediaPlayer->state() == Vlc::Buffering ||
        _vlcMediaPlayer->state() == Vlc::Playing ||
        _vlcMediaPlayer->state() == Vlc::Paused)
        _vlcAudio->setVolume(_currentVolume);
}

int VlcWidgetVolumeSlider::volume() const
{
    return _currentVolume;
}

void VlcWidgetVolumeSlider::volumeControl(const bool &up)
{
    if (up) {
        if (_currentVolume != 200) {
            setVolume(_currentVolume + 1);
        }
    } else {
        if (_currentVolume != 0) {
            setVolume(_currentVolume - 1);
        }
    }
}

void VlcWidgetVolumeSlider::lock()
{
    _lock = true;
}

void VlcWidgetVolumeSlider::unlock()
{
    _lock = false;
}
