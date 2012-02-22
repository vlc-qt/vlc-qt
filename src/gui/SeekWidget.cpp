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

#include <QtCore/QTime>
#include <QtGui/QHBoxLayout>

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "gui/SeekWidget.h"

VlcSeekWidget::VlcSeekWidget(VlcMediaPlayer *player,
                             QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(player),
      _autoHide(false)
{
    _seek = new QSlider(this);
    _seek->setOrientation(Qt::Horizontal);
    _seek->setMaximum(0);
    _seek->setPageStep(1000);

    _labelElapsed = new QLabel(this);
    _labelElapsed->setText("00:00:00");

    _labelFull = new QLabel(this);
    _labelFull->setText("00:00:00");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_labelElapsed);
    layout->addWidget(_seek);
    layout->addWidget(_labelFull);
    setLayout(layout);

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(_seek, SIGNAL(sliderReleased()), this, SLOT(changeTime()));

    _timer->start(400);
}

VlcSeekWidget::VlcSeekWidget(QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(0),
      _autoHide(false)
{
    _seek = new QSlider(this);
    _seek->setOrientation(Qt::Horizontal);
    _seek->setMaximum(0);
    _seek->setPageStep(1000);

    _labelElapsed = new QLabel(this);
    _labelElapsed->setText("00:00:00");

    _labelFull = new QLabel(this);
    _labelFull->setText("00:00:00");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_labelElapsed);
    layout->addWidget(_seek);
    layout->addWidget(_labelFull);
    setLayout(layout);

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(_seek, SIGNAL(sliderReleased()), this, SLOT(changeTime()));
}

VlcSeekWidget::~VlcSeekWidget()
{
    delete _seek;
    delete _labelElapsed;
    delete _labelFull;
    delete _timer;
}

void VlcSeekWidget::setMediaPlayer(VlcMediaPlayer *player)
{
    _vlcMediaPlayer = player;

    _timer->start(400);
}

void VlcSeekWidget::updateTime()
{
    if (_vlcMediaPlayer->state() == Vlc::Buffering ||
       _vlcMediaPlayer->state() == Vlc::Playing ||
       _vlcMediaPlayer->state() == Vlc::Paused) {
        int fullTime = _vlcMediaPlayer->lenght();
        int currentTime = _vlcMediaPlayer->time();

        _labelFull->setText(QTime(0,0,0,0).addMSecs(fullTime).toString("hh:mm:ss"));
        _seek->setMaximum(fullTime);

        _labelElapsed->setText(QTime(0,0,0,0).addMSecs(currentTime).toString("hh:mm:ss"));
        _seek->setValue(currentTime);

        if (_autoHide && !fullTime) {
            setVisible(false);
        } else {
            setVisible(true);
        }
    } else {
        _labelFull->setText("00:00:00");
        _seek->setMaximum(0);

        _labelElapsed->setText("00:00:00");
        _seek->setValue(0);

        if (_autoHide) {
            setVisible(false);
        }
    }
}

void VlcSeekWidget::changeTime()
{
    if (!_vlcMediaPlayer->core())
        return;

    _labelElapsed->setText(QTime(0,0,0,0).addMSecs(_seek->value()).toString("hh:mm:ss"));

    _vlcMediaPlayer->setTime(_seek->value());
}
