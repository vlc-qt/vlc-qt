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

#include <QtCore/QDebug>

#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include <vlc/vlc.h>

#include "TestRecorder.h"
#include "ui_TestRecorder.h"

TestRecorder::TestRecorder(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::TestRecorder)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _media = new VlcMedia("http://192.168.1.50:1234/udp/232.4.1.1:5002", _instance);
    _media->record("test", "/home/tadej/Video/Tano", Vlc::MP4);

    _timer = new QTimer(this);
    _timer->setSingleShot(true);

    connect(_timer, SIGNAL(timeout()), this, SLOT(stop()));
    connect(ui->buttonPlay, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->buttonStop, SIGNAL(clicked()), this, SLOT(stop()));
}

TestRecorder::~TestRecorder()
{
    delete ui;
    delete _timer;
    delete _media;
    delete _player;
    delete _instance;
}

void TestRecorder::play()
{
    qDebug() << "Start";

    _player->open(_media);
    _timer->start(10000);
}

void TestRecorder::stop()
{
    _player->stop();

    qDebug() << "Stop";
}
