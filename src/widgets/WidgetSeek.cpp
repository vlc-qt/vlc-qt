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

#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QProgressBar>
#else
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QLabel>
    #include <QtGui/QProgressBar>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"

#include "widgets/WidgetSeek.h"

VlcWidgetSeek::VlcWidgetSeek(VlcMediaPlayer *player,
                             QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(player)
{
    initWidgetSeek();
}

VlcWidgetSeek::VlcWidgetSeek(QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(0)
{
    initWidgetSeek();
}

VlcWidgetSeek::~VlcWidgetSeek()
{
    delete _seek;
    delete _labelElapsed;
    delete _labelFull;
}

void VlcWidgetSeek::initWidgetSeek()
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

void VlcWidgetSeek::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();

    if (!_lock)
        return;

    updateEvent(event->pos());
}

void VlcWidgetSeek::mousePressEvent(QMouseEvent *event)
{
    event->ignore();

    lock();
}

void VlcWidgetSeek::mouseReleaseEvent(QMouseEvent *event)
{
    event->ignore();

    updateEvent(event->pos());

    unlock();
}

void VlcWidgetSeek::wheelEvent(QWheelEvent *event)
{
    event->ignore();

    if (!_vlcMediaPlayer)
        return;

    if (event->delta() > 0)
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() + _vlcMediaPlayer->length() * 0.01);
    else
        _vlcMediaPlayer->setTime(_vlcMediaPlayer->time() - _vlcMediaPlayer->length() * 0.01);
}

void VlcWidgetSeek::setAutoHide(bool autoHide)
{
    _autoHide = autoHide;

    setVisible(!_autoHide);
}

void VlcWidgetSeek::setMediaPlayer(VlcMediaPlayer *player)
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

void VlcWidgetSeek::end()
{
    QTime time = QTime(0,0,0,0);
    QString display = "mm:ss";

    _labelElapsed->setText(time.toString(display));
    _labelFull->setText(time.toString(display));
    _seek->setMaximum(1);
    _seek->setValue(0);
}

void VlcWidgetSeek::updateEvent(const QPoint &pos)
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

void VlcWidgetSeek::updateCurrentTime(int time)
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


void VlcWidgetSeek::updateFullTime(int time)
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
        setVisible(true);
    }
}

void VlcWidgetSeek::lock()
{
    _lock = true;
}

void VlcWidgetSeek::unlock()
{
    _lock = false;
}
