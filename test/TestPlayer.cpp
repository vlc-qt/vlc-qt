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
#include "core/MediaPlayer.h"

#include "TestPlayer.h"
#include "ui_TestPlayer.h"

TestPlayer::TestPlayer(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::TestPlayer)
{
	ui->setupUi(this);

	_instance = new VlcInstance(VlcCommon::args(), this);
	_player = new VlcMediaPlayer(ui->video->widgetId(), this);
	ui->volume->setVolume(50);

	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
}

TestPlayer::~TestPlayer()
{
	delete ui;
	delete _instance;
	delete _player;
}

void TestPlayer::open()
{
	QString file =
		QFileDialog::getOpenFileName(this, tr("Open file or URL"),
						QDir::homePath(),
						tr("Multimedia files(*)"));

	if (file.isEmpty())
		return;

	_player->open(file);
}
