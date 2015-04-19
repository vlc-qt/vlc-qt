/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

// QtGui/QtWidgets
#include <QFileDialog>

#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "DualPlayer.h"
#include "ui_Dual.h"

DualPlayer::DualPlayer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Dual),
      _media1(0),
      _media2(0)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);

    _player1 = new VlcMediaPlayer(_instance);
    _player1->setVideoWidget(ui->video1);

    ui->video1->setMediaPlayer(_player1);

    connect(ui->open1, SIGNAL(clicked()), this, SLOT(open1()));
    connect(ui->pause1, SIGNAL(clicked()), _player1, SLOT(pause()));
    connect(ui->stop1, SIGNAL(clicked()), _player1, SLOT(stop()));

    _player2 = new VlcMediaPlayer(_instance);
    _player2->setVideoWidget(ui->video2);

    ui->video2->setMediaPlayer(_player2);

    connect(ui->open2, SIGNAL(clicked()), this, SLOT(open2()));
    connect(ui->pause2, SIGNAL(clicked()), _player2, SLOT(pause()));
    connect(ui->stop2, SIGNAL(clicked()), _player2, SLOT(stop()));

    ui->group1->setTitle("Player 1");
    ui->group2->setTitle("Player 2");

    setWindowTitle("Dual Player Test");
}

DualPlayer::~DualPlayer()
{
    delete _media1;
    delete _player1;
    delete _media2;
    delete _player2;
    delete _instance;
    delete ui;
}

void DualPlayer::open1()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media1 = new VlcMedia(file, true, _instance);

    _player1->open(_media1);
}

void DualPlayer::open2()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media2 = new VlcMedia(file, true, _instance);

    _player2->open(_media2);
}
