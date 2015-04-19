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

#include "core/Common.h"

#include "Tests.h"
#include "ui_Tests.h"

#include "common/dual/DualInstance.h"
#include "common/dual/DualPlayer.h"
#include "common/MetaManager.h"
#include "common/Recorder.h"
#include "widgets/Player.h"

Tests::Tests(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Tests),
#if QT_VERSION >= 0x050000
      _quickView(0),
#endif
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

#if QT_VERSION >= 0x050000
    connect(ui->buttonQml, SIGNAL(clicked()), this, SLOT(qml()));
#endif
}

Tests::~Tests()
{
    delete ui;

    delete _testDualInstance;
    delete _testDualPlayer;
    delete _testPlayer;

#if QT_VERSION >= 0x050000
    delete _quickView;
#endif
}

void Tests::dualInstance()
{
    if(_testDualInstance) {
        delete _testDualInstance;
    }

    _testDualInstance = new DualInstance(this);
    _testDualInstance->show();
}

void Tests::dualPlayer()
{
    if(_testDualPlayer) {
        delete _testDualPlayer;
    }

    _testDualPlayer = new DualPlayer(this);
    _testDualPlayer->show();
}

void Tests::metaManager()
{
    MetaManager test;
    test.exec();
}

void Tests::player()
{
    if(_testPlayer) {
        delete _testPlayer;
    }

    _testPlayer = new Player(this);
    _testPlayer->show();
}

void Tests::qml()
{
#if QT_VERSION >= 0x050000
    if(_quickView) {
        delete _quickView;
    }

    _quickView = new QQuickView();
    _quickView->setSource(QUrl(QStringLiteral("qrc:/qml/video.qml")));
    _quickView->setResizeMode(QQuickView::SizeRootObjectToView);
    _quickView->show();
#endif
}

void Tests::recorder()
{
    Recorder test;
    test.exec();
}
