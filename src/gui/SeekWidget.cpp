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
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#if defined(Qt5)
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QProgressBar>
#elif defined(Qt4)
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QLabel>
    #include <QtGui/QProgressBar>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "gui/SeekWidget.h"

VlcSeekWidget::VlcSeekWidget(VlcMediaPlayer *player,
                             QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(player)
{
    initSeekWidget();
}

VlcSeekWidget::VlcSeekWidget(QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(0)
{
    initSeekWidget();
}

VlcSeekWidget::~VlcSeekWidget()
{
    delete _seek;
    delete _labelElapsed;
    delete _labelFull;
    delete _timer;
}

void VlcSeekWidget::initSeekWidget()
{
    _lock = false;
    _autoHide = false;

    _seek = new QProgressBar(this);
    _seek->setOrientation(Qt::Horizontal);
    _seek->setMaximum(1);
    _seek->setTextVisible(false);
    _seek->setMaximumHeight(15);

    _labelElapsed = new QLabel(this);
    _labelElapsed->setText("00:00");

    _labelFull = new QLabel(this);
    _labelFull->setText("00:00");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_labelElapsed);
    layout->addWidget(_seek);
    layout->addWidget(_labelFull);
    setLayout(layout);

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    _timer->start(100);
}

void VlcSeekWidget::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    lock();
}

void VlcSeekWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();

    if (!_vlcMediaPlayer->core())
        return;

    if (event->pos().x() < _seek->pos().x() || event->pos().x() > _seek->pos().x() + _seek->width())
        return;

    float click = event->pos().x() - _seek->pos().x();
    float op = _seek->maximum()/_seek->width();
    float newValue = click * op;

    _vlcMediaPlayer->setTime(newValue);

    unlock();
}

void VlcSeekWidget::wheelEvent(QWheelEvent *event)
{
    event->ignore();

    if (!_vlcMediaPlayer->core())
        return;

    if (event->delta() > 0)
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() + _vlcMediaPlayer->lenght() * 0.01);
    else
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() - _vlcMediaPlayer->lenght() * 0.01);
}

void VlcSeekWidget::setMediaPlayer(VlcMediaPlayer *player)
{
    _vlcMediaPlayer = player;

    _timer->start(100);
}

void VlcSeekWidget::updateTime()
{
    if (_lock)
        return;

    if (_vlcMediaPlayer->state() == Vlc::Buffering ||
       _vlcMediaPlayer->state() == Vlc::Playing ||
       _vlcMediaPlayer->state() == Vlc::Paused) {
        int full = _vlcMediaPlayer->lenght();
        int current = _vlcMediaPlayer->time();
        QTime fullTime = QTime(0,0,0,0).addMSecs(_vlcMediaPlayer->lenght());
        QTime currentTime = QTime(0,0,0,0).addMSecs(_vlcMediaPlayer->time());

        QString display = "mm:ss";
        if (fullTime.hour() > 0)
            display = "hh:mm:ss";

        _labelFull->setText(fullTime.toString(display));
        _seek->setMaximum(full);

        _labelElapsed->setText(currentTime.toString(display));
        _seek->setValue(current);

        if (_autoHide && !full) {
            setVisible(false);
        } else {
            setVisible(true);
        }
    } else {
        _labelFull->setText("00:00");
        _seek->setMaximum(1);

        _labelElapsed->setText("00:00");
        _seek->setValue(0);

        if (_autoHide) {
            setVisible(false);
        }
    }
}

void VlcSeekWidget::lock()
{
    _lock = true;
}

void VlcSeekWidget::unlock()
{
    _lock = false;
}
