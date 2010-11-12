/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
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

#include "TestMain.h"
#include "ui_TestMain.h"

#include "TestMetaManager.h"

TestMain::TestMain(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::TestMain)
{
	ui->setupUi(this);

	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(ui->buttonMetaManager, SIGNAL(clicked()), this, SLOT(metaManagerTest()));
}

TestMain::~TestMain()
{
	delete ui;
}

void TestMain::metaManagerTest()
{
	TestMetaManager test;
	test.exec();
}
