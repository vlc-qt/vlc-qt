/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* AudioControl.h: Audio controller
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#include "core/Audio.h"
#include "core/MediaPlayer.h"
#include "gui/AudioControl.h"

VlcAudioControl::VlcAudioControl(QObject *parent) :
	QObject(parent),
	_actionList(QList<QAction*>()),
	_map(QMap<QString,int>()),
	_actionGroup(0)
{
	_timer = new QTimer(this);
	connect(_timer, SIGNAL(timeout()), this, SLOT(updateActions()));

	_timer->start(2000);
}


VlcAudioControl::~VlcAudioControl()
{
	clean();

	delete _timer;
}

void VlcAudioControl::clean()
{
	for(int i=0; i<_actionList.size(); i++)
		delete _actionList[i];
	_actionList.clear();
	_map.clear();
	if(_actionGroup)
		delete _actionGroup;
}

void VlcAudioControl::reset()
{
	_timer->start(2000);
}

void VlcAudioControl::update()
{
	int id = _map.value(_actionGroup->checkedAction()->text());

	VlcAudio::setTrack(id);
}

void VlcAudioControl::updateActions()
{
	clean();
	_actionGroup = new QActionGroup(this);

	if(!VlcMediaPlayer::isActive()) {
		emit actions("audio", _actionList);
		return;
	}

	if(VlcAudio::trackCount() > 0) {
		QStringList desc = VlcAudio::trackDescription();
		for(int i = 0; i < desc.size(); i++) {
			_map.insert(desc[i], i);
			_actionList << new QAction(desc[i], this);
		}
	} else {
		emit actions("audio", _actionList);
		return;
	}

	for (int i = 0; i < _actionList.size(); ++i) {
		_actionList[i]->setCheckable(true);
		_actionGroup->addAction(_actionList[i]);
		connect(_actionList[i], SIGNAL(triggered()), this, SLOT(update()));
	}

	_actionList[VlcAudio::track()]->setChecked(true);

	emit actions("audio", _actionList);

	_timer->start(60000);
}
