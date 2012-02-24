/****************************************************************************
* VLC-Qt CMake Demo
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

#include <QtGui/QFileDialog>

#include <vlc-qt/Common.h>
#include <vlc-qt/Instance.h>
#include <vlc-qt/Media.h>
#include <vlc-qt/MediaPlayer.h>

#include "DemoPlayer.h"
#include "ui_DemoPlayer.h"

DemoPlayer::DemoPlayer(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::DemoPlayer),
    _media(0)
{
  ui->setupUi(this);

  _instance = new VlcInstance(VlcCommon::args(), this);
  _player = new VlcMediaPlayer(_instance);
  _player->setVideoWidgetId(ui->video->widgetId());

  ui->video->setMediaPlayer(_player);
  ui->volume->setMediaPlayer(_player);
  ui->volume->setVolume(50);
  ui->seek->setMediaPlayer(_player);

  connect(ui->open, SIGNAL(clicked()), this, SLOT(open()));
  connect(ui->pause, SIGNAL(clicked()), _player, SLOT(pause()));
  connect(ui->stop, SIGNAL(clicked()), _player, SLOT(stop()));
}

DemoPlayer::~DemoPlayer()
{
    delete ui;
    delete _instance;
    delete _media;
    delete _player;
}

void DemoPlayer::open()
{
    QString file =
        QFileDialog::getOpenFileName(this, tr("Open file or URL"),
                        QDir::homePath(),
                        tr("Multimedia files(*)"));

    if (file.isEmpty())
        return;

    _media = new VlcMedia(file, true, _instance);

    _player->open(_media);
}
