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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "core/Common.h"

#include "TestRecorder.h"
#include "ui_TestRecorder.h"

TestRecorder::TestRecorder(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::TestRecorder)
{
	ui->setupUi(this);

	QString file = "/home/tadej/Videos/Tano/test.ts";

	_instance = new VlcInstance(Vlc::recorderArgs(file), this);
	_player = new VlcMediaPlayer();

	_player->open("udp://@232.4.1.1:5002");
	_player->play();
}

TestRecorder::~TestRecorder()
{
	delete ui;
	delete _instance;
}
