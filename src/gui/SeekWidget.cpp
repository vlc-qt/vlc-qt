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
}

void VlcSeekWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();

    if (!_lock)
        return;

    updateEvent(event->pos());
}

void VlcSeekWidget::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    lock();
}

void VlcSeekWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();

    updateEvent(event->pos());

    unlock();
}

void VlcSeekWidget::wheelEvent(QWheelEvent *event)
{
    event->ignore();

    if (!_vlcMediaPlayer)
        return;

    if (event->delta() > 0)
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() + _vlcMediaPlayer->lenght() * 0.01);
    else
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() - _vlcMediaPlayer->lenght() * 0.01);
}

void VlcSeekWidget::setAutoHide(const bool &autoHide)
{
    _autoHide = autoHide;

    setVisible(!_autoHide);
}

void VlcSeekWidget::setMediaPlayer(VlcMediaPlayer *player)
{
    if (_vlcMediaPlayer) {
        disconnect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
        disconnect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
    }

    _vlcMediaPlayer = player;

    connect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
    connect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
}

void VlcSeekWidget::end()
{
    QTime time = QTime(0,0,0,0);
    QString display = "mm:ss";

    _labelElapsed->setText(time.toString(display));
    _labelFull->setText(time.toString(display));
    _seek->setMaximum(1);
    _seek->setValue(0);
}

void VlcSeekWidget::updateEvent(const QPoint &pos)
{
    if (!_vlcMediaPlayer)
        return;

    if (pos.x() < _seek->pos().x() || pos.x() > _seek->pos().x() + _seek->width())
        return;

    float click = pos.x() - _seek->pos().x();
    float op = _seek->maximum()/_seek->width();
    float newValue = click * op;

    _vlcMediaPlayer->setTime(newValue);
    _seek->setValue(newValue);
}

void VlcSeekWidget::updateCurrentTime(const int &time)
{
    if (_lock)
        return;

    QTime currentTime = QTime(0,0,0,0).addMSecs(time);

    QString display = "mm:ss";
    if (currentTime.hour() > 0)
        display = "hh:mm:ss";

    _labelElapsed->setText(currentTime.toString(display));
    _seek->setValue(time);
}


void VlcSeekWidget::updateFullTime(const int &time)
{
    if (_lock)
        return;

    QTime fullTime = QTime(0,0,0,0).addMSecs(time);

    QString display = "mm:ss";
    if (fullTime.hour() > 0)
        display = "hh:mm:ss";

    _labelFull->setText(fullTime.toString(display));

    if (!time) {
        _seek->setMaximum(1);
        setVisible(!_autoHide);
    } else {
        _seek->setMaximum(time);
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
