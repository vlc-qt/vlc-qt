/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>

#include "core/Common.h"

#include "TestMain.h"
#include "ui_TestMain.h"

#include "TestMetaManager.h"
#include "TestPlayer.h"
#include "TestRecorder.h"

TestMain::TestMain(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::TestMain),
	_testPlayer(0)
{
	ui->setupUi(this);

	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(ui->buttonLib, SIGNAL(clicked()), this, SLOT(libTest()));
	connect(ui->buttonMetaManager, SIGNAL(clicked()), this, SLOT(metaManagerTest()));
	connect(ui->buttonPlayer, SIGNAL(clicked()), this, SLOT(playerTest()));
	connect(ui->buttonRecorder, SIGNAL(clicked()), this, SLOT(recorderTest()));
}

TestMain::~TestMain()
{
	delete ui;
}

void TestMain::libTest()
{
	QStringList args = VlcCommon::args();
	std::string stdStrings[args.size()];
	const char *vlcArgs[args.size()];
	for(int i = 0; i < args.size(); i++) {
		stdStrings[i] = args[i].toStdString();
		vlcArgs[i] = stdStrings[i].c_str();
	}

	QString path = "/home/tadej/Videos/Yugo.mpeg";
	std::string pathstd = path.toStdString();
	const char * p = pathstd.c_str();

	_instance = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);
	libvlc_media_t *media = libvlc_media_new_path(_instance, p);
	_player = libvlc_media_player_new_from_media(media);
	libvlc_media_player_play(_player);
}

void TestMain::metaManagerTest()
{
	TestMetaManager test;
	test.exec();
}

void TestMain::playerTest()
{
	if(_testPlayer) {
		delete _testPlayer;
	}

	_testPlayer = new TestPlayer(this);
	_testPlayer->show();
}

void TestMain::recorderTest()
{
	TestRecorder test;
	test.exec();
}
