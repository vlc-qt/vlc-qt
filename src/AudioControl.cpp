/****************************************************************************
* VLC-Qt - Qt and libVLC connector library
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

#include "AudioControl.h"
#include "core/Error.h"
#include "core/MediaPlayer.h"

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
	delete _timer;

	for(int i=0; i<_actionList.size(); i++)
		delete _actionList[i];
	if(_actionGroup)
		delete _actionGroup;
}

void VlcAudioControl::updateActions()
{
	for(int i=0; i<_actionList.size(); i++)
		delete _actionList[i];
	_actionList.clear();
	_map.clear();

	if(_actionGroup)
		delete _actionGroup;
	_actionGroup = new QActionGroup(this);

	if(!VlcMediaPlayer::isActive()) {
		emit actions("audio", _actionList);
		return;
	}

	if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) != 0) {
		libvlc_track_description_t *desc;
		desc = libvlc_audio_get_track_description(_vlcCurrentMediaPlayer);
		_map.insert(QString().fromUtf8(desc->psz_name), 0);
		_actionList << new QAction(QString().fromUtf8(desc->psz_name), this);

		if(libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) > 1) {
			for(int i = 1; i < libvlc_audio_get_track_count(_vlcCurrentMediaPlayer); i++) {
				desc = desc->p_next;
				_map.insert(QString().fromUtf8(desc->psz_name), i);
				_actionList << new QAction(QString().fromUtf8(desc->psz_name), this);
			}
		}

	} else {
		emit actions("audio", _actionList);
		return;
	}

	VlcError::errmsg();

	for (int i = 0; i < _actionList.size(); ++i) {
		_actionList[i]->setCheckable(true);
		_actionGroup->addAction(_actionList[i]);
		connect(_actionList[i], SIGNAL(triggered()), this, SLOT(update()));
	}


	_actionList[libvlc_audio_get_track(_vlcCurrentMediaPlayer)]->setChecked(true);
	VlcError::errmsg();

	emit actions("audio", _actionList);

	_timer->start(60000);
}

void VlcAudioControl::update()
{
	int id = _map.value(_actionGroup->checkedAction()->text());

	libvlc_audio_set_track(_vlcCurrentMediaPlayer, id);

	VlcError::errmsg();
}

void VlcAudioControl::reset()
{
	_timer->start(2000);
}
