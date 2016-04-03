/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "Player.h"
#include "ui_Player.h"

Player::Player(VlcInstance *instance,
               QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Player),
      _instance(instance)
{
    ui->setupUi(this);

    if (!_instance->status())
        return;

    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->pause, SIGNAL(toggled(bool)), _player, SLOT(togglePause()));
    connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));

    _media = new VlcMedia("http://download.blender.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_surround-fix.avi", _instance);
    _player->open(_media);
}

Player::~Player()
{
    if (_instance->status()) {
        _player->stop();

        delete _media;
        delete _player;
    }
    delete _instance;
    delete ui;
}
