/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
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

#include <QtCore/QDebug>
#include <QtCore/QDir>

#if defined(Qt5)
    #include <QtWidgets/QFileDialog>
#elif defined(Qt4)
    #include <QtGui/QFileDialog>
#endif

#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "TestRecorder.h"
#include "ui_TestRecorder.h"

TestRecorder::TestRecorder(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::TestRecorder),
      _media(0)
{
    ui->setupUi(this);

    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);

    _timer = new QTimer(this);
    _timer->setSingleShot(true);

    ui->editPath->setText(QDir::homePath() + "/Videos");

    ui->comboAudio->addItems(Vlc::audioCodec());
    ui->comboMux->addItems(Vlc::mux());
    ui->comboVideo->addItems(Vlc::videoCodec());

    connect(_timer, SIGNAL(timeout()), this, SLOT(stop()));
    connect(ui->buttonBrowse, SIGNAL(clicked()), this, SLOT(browse()));
    connect(ui->buttonPlay, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->buttonStop, SIGNAL(clicked()), this, SLOT(stop()));
}

TestRecorder::~TestRecorder()
{
    delete ui;
    delete _timer;
    delete _media;
    delete _player;
    delete _instance;
}

void TestRecorder::browse()
{
    QString path =
            QFileDialog::getExistingDirectory(this, QObject::tr("Open directory"),
                                              ui->editPath->text(),
                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->editPath->setText(path);
}

void TestRecorder::play()
{
    qDebug() << "Start";

    if (_media)
        delete _media;

    _media = new VlcMedia(ui->editUrl->text(), _instance);
    _media->record(ui->editName->text(), ui->editPath->text(),
                   Vlc::Mux(ui->comboMux->currentIndex()),
                   Vlc::AudioCodec(ui->comboAudio->currentIndex()),
                   Vlc::VideoCodec(ui->comboVideo->currentIndex()));

    _player->open(_media);
    _timer->start(10000);
}

void TestRecorder::stop()
{
    _player->stop();

    qDebug() << "Stop";
}
