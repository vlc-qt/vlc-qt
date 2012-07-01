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

#include "core/Common.h"

#include "TestMain.h"
#include "ui_TestMain.h"

#include "TestDualInstance.h"
#include "TestDualPlayer.h"
#include "TestMetaManager.h"
#include "TestPlayer.h"
#include "TestRecorder.h"

TestMain::TestMain(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::TestMain),
      _testDualInstance(0),
      _testDualPlayer(0),
      _testPlayer(0)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->buttonDualInstance, SIGNAL(clicked()), this, SLOT(dualInstance()));
    connect(ui->buttonDualPlayer, SIGNAL(clicked()), this, SLOT(dualPlayer()));
    connect(ui->buttonMetaManager, SIGNAL(clicked()), this, SLOT(metaManager()));
    connect(ui->buttonPlayer, SIGNAL(clicked()), this, SLOT(player()));
    connect(ui->buttonRecorder, SIGNAL(clicked()), this, SLOT(recorder()));
}

TestMain::~TestMain()
{
    delete ui;

    delete _testDualInstance;
    delete _testDualPlayer;
    delete _testPlayer;
}

void TestMain::dualInstance()
{
    if(_testDualInstance) {
        delete _testDualInstance;
    }

    _testDualInstance = new TestDualInstance(this);
    _testDualInstance->show();
}

void TestMain::dualPlayer()
{
    if(_testDualPlayer) {
        delete _testDualPlayer;
    }

    _testDualPlayer = new TestDualPlayer(this);
    _testDualPlayer->show();
}

void TestMain::metaManager()
{
    TestMetaManager test;
    test.exec();
}

void TestMain::player()
{
    if(_testPlayer) {
        delete _testPlayer;
    }

    _testPlayer = new TestPlayer(this);
    _testPlayer->show();
}

void TestMain::recorder()
{
    TestRecorder test;
    test.exec();
}
