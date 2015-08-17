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

#include <QtCore/QDebug>
// QtGui/QtWidgets
#include <QFileDialog>
#include <QInputDialog>

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#if LIBVLC_VERSION >= 0x020200
    #include "EqualizerDialog.h"
#endif

#include "Player.h"
#include "ui_Player.h"

Player::Player(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Player),
      _media(0)
#if LIBVLC_VERSION >= 0x020200
      , _equalizerDialog(new EqualizerDialog(this))
#endif
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);
#if LIBVLC_VERSION >= 0x020200
    _equalizerDialog->setMediaPlayer(_player);
#endif

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->actionOpenLocal, SIGNAL(triggered()), this, SLOT(openLocal()));
    connect(ui->actionOpenUrl, SIGNAL(triggered()), this, SLOT(openUrl()));
    connect(ui->actionPause, SIGNAL(triggered()), _player, SLOT(pause()));
    connect(ui->actionStop, SIGNAL(triggered()), _player, SLOT(stop()));
    connect(ui->openLocal, SIGNAL(clicked()), this, SLOT(openLocal()));
    connect(ui->openUrl, SIGNAL(clicked()), this, SLOT(openUrl()));
    connect(ui->pause, SIGNAL(clicked()), _player, SLOT(pause()));
    connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));
#if LIBVLC_VERSION >= 0x020200
    connect(ui->equalizer, SIGNAL(clicked()), _equalizerDialog, SLOT(show()));
#else
    ui->equalizer->hide();
#endif
    connect(ui->functionTest, SIGNAL(clicked()), this, SLOT(functionTest()));
}

Player::~Player()
{
    delete _player;
    delete _media;
    delete _instance;
    delete ui;
}

void Player::openLocal()
{
    QString file =
            QFileDialog::getOpenFileName(this, tr("Open file"),
                                         QDir::homePath(),
                                         tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media = new VlcMedia(file, true, _instance);

    _player->open(_media);
}

void Player::openUrl()
{
    QString url =
            QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));

    if (url.isEmpty())
        return;

    _media = new VlcMedia(url, _instance);

    _player->open(_media);
}

void Player::functionTest()
{
    // Testing placeholder function

    VlcAudio *audio = new VlcAudio(_player);

    qDebug() << audio->channel();

    audio->setChannel(Vlc::Left);

    qDebug() << audio->channel();
}
