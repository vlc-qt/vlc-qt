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

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaList.h"
#include "core/MediaListPlayer.h"
#include "core/MediaPlayer.h"

#include "MediaList.h"
#include "ui_MediaList.h"

MediaList::MediaList(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MediaList)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _player->setVideoWidget(ui->video);

    _listPlayer = new VlcMediaListPlayer(_player, _instance);

    ui->video->setMediaPlayer(_player);
    ui->volume->setMediaPlayer(_player);
    ui->volume->setVolume(50);
    ui->seek->setMediaPlayer(_player);

    connect(ui->actionPause, SIGNAL(triggered()), _player, SLOT(pause()));
    connect(ui->actionStop, SIGNAL(triggered()), _player, SLOT(stop()));
    connect(ui->pause, SIGNAL(clicked()), _player, SLOT(pause()));
    connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));
    connect(ui->previous, SIGNAL(clicked()), _listPlayer, SLOT(previous()));
    connect(ui->next, SIGNAL(clicked()), _listPlayer, SLOT(next()));

    _mediaList = new VlcMediaList(_instance);
    _mediaList->addMedia(new VlcMedia("http://videos.hd-trailers.net/e23ab4b8-a737-46dd-a0e4-259ba36056b6_YsfXbEghC5XywlmkKiYrF0D1oWcPYHA94aPeKmTuUKJJVJBpH4AFbPzcNWMhAJHuRnKZAAatvKg-_8_0.mp4", _instance));
    _mediaList->addMedia(new VlcMedia("https://www.dropbox.com/s/zeq9meq2j7gfggn/234H.jpg?dl=1", _instance));
    _mediaList->addMedia(new VlcMedia("http://videos.hd-trailers.net/e23ab4b8-a737-46dd-a0e4-259ba36056b6_YsfXbEghC5XywlmkKiYrF0D1oWcPYHA94aPeKmTuUKJJVJBpH4AFbPzcNWMhAJHuRnKZAAatvKg-_8_0.mp4", _instance));

    _listPlayer->setMediaList(_mediaList);
    _listPlayer->mediaPlayer()->play();
}

MediaList::~MediaList()
{
    delete _player;
    delete _mediaList;
    delete _instance;
    delete ui;
}
