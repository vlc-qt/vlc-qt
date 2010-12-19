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

#include <QtCore/QDebug>
#include <QtGui/QFileDialog>

#include "core/Common.h"

#include "TestMetaManager.h"
#include "ui_TestMetaManager.h"

TestMetaManager::TestMetaManager(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::TestMetaManager)
{
	ui->setupUi(this);

	connect(ui->buttonOpen, SIGNAL(clicked()), this, SLOT(open()));
	connect(ui->buttonRead, SIGNAL(clicked()), this, SLOT(read()));
	connect(ui->buttonSet, SIGNAL(clicked()), this, SLOT(set()));
	connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(save()));

	_instance = new VlcInstance(Vlc::commonArgs(), this);
}

TestMetaManager::~TestMetaManager()
{
	delete ui;
	delete _meta;
	delete _media;
	delete _instance;
}

void TestMetaManager::open()
{
	if(_meta)
		delete _meta;
	if(_media)
		delete _media;

	QString m = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "mp3 (*.mp3)");
	_media = new VlcMedia(m, this);
	_meta = new VlcMetaManager(_media);
}

void TestMetaManager::read()
{
	QString album("Album: " + _meta->album());
	QString artist("Artist: " + _meta->artist());
	QString artwork("Artwork: " + _meta->artwork());
	QString copyright("Copyright: " + _meta->copyright());
	QString description("Description: " + _meta->description());
	QString encoder("Encoder: " + _meta->encoder());
	QString genre("Genre: " + _meta->genre());
	QString id("ID: " + _meta->id());
	QString language("Language: " + _meta->language());
	QString number("Number: " + QString().number(_meta->number()));
	QString publisher("Publisher: " + _meta->publisher());
	QString rating("Rating: " + _meta->rating());
	QString setting("Setting: " + _meta->setting());
	QString title("Title: " + _meta->title());
	QString url("Url: " + _meta->url());
	QString year("Year: " + QString().number(_meta->year()));

	ui->labelMeta->setText(album + "\n" + artist + "\n" + artwork + "\n" + copyright + "\n" +
						   description + "\n" + encoder + "\n" + genre + "\n" + id + "\n" +
						   language + "\n" + number + "\n" + publisher + "\n" + rating + "\n" +
						   setting + "\n" + title + "\n" + url + "\n" + year + "\n");
}

void TestMetaManager::save()
{
	if(_meta->saveMeta())
		ui->labelSave->setText("Successfully saved!");
}

void TestMetaManager::set()
{
	_meta->setAlbum(ui->edit->text());
	_meta->setArtist(ui->edit->text());
	_meta->setCopyright(ui->edit->text());
	_meta->setDescription(ui->edit->text());
	_meta->setEncoder(ui->edit->text());
	_meta->setGenre(ui->edit->text());
	_meta->setLanguage(ui->edit->text());
	_meta->setNumber(999); // Default test
	_meta->setPublisher(ui->edit->text());
	_meta->setTitle(ui->edit->text());
	_meta->setYear(1789); // Default test
}
