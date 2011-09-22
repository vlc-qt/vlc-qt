/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <tadej@tano.si>
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

#include <QtGui/QFileDialog>

#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "TestDualPlayer.h"
#include "ui_TestDual.h"

TestDualPlayer::TestDualPlayer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::TestDual),
      _media1(0),
      _media2(0)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);

    _player1 = new VlcMediaPlayer(_instance);
    _player1->setVideoWidgetId(ui->video1->widgetId());

    ui->video1->setMediaPlayer(_player1);
    ui->volume1->setMediaPlayer(_player1);
    ui->volume1->setVolume(50);
    ui->seek1->setMediaPlayer(_player1);

    connect(ui->open1, SIGNAL(clicked()), this, SLOT(open1()));
    connect(ui->pause1, SIGNAL(clicked()), _player1, SLOT(pause()));
    connect(ui->stop1, SIGNAL(clicked()), _player1, SLOT(stop()));

    _player2 = new VlcMediaPlayer(_instance);
    _player2->setVideoWidgetId(ui->video2->widgetId());

    ui->video2->setMediaPlayer(_player2);
    ui->volume2->setMediaPlayer(_player2);
    ui->volume2->setVolume(50);
    ui->seek2->setMediaPlayer(_player2);

    connect(ui->open2, SIGNAL(clicked()), this, SLOT(open2()));
    connect(ui->pause2, SIGNAL(clicked()), _player2, SLOT(pause()));
    connect(ui->stop2, SIGNAL(clicked()), _player2, SLOT(stop()));
}

TestDualPlayer::~TestDualPlayer()
{
    delete ui;
    delete _instance;
    delete _player1;
    delete _media1;
    delete _player2;
    delete _media2;
}

void TestDualPlayer::open1()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file or URL"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media1 = new VlcMedia(file, _instance);

    _player1->open(_media1);
}

void TestDualPlayer::open2()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file or URL"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media2 = new VlcMedia(file, _instance);

    _player2->open(_media2);
}
