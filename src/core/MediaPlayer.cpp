/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* MediaPlayer.cpp: MediaPlayer
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

#include <QtCore/QDebug>

#include "core/Error.h"
#include "core/MediaPlayer.h"

libvlc_media_player_t *_vlcCurrentMediaPlayer = NULL;

VlcMediaPlayer::VlcMediaPlayer(const WId &widget,
							   QObject *parent) :
	QObject(parent),
	_vlcMedia(NULL),
	_widgetId(widget)
{
	_check = new QTimer(this);
	connect(_check, SIGNAL(timeout()), this, SLOT(checkPlayingState()));
	_check->start(300);

}

VlcMediaPlayer::~VlcMediaPlayer()
{
	delete _check;
}

void VlcMediaPlayer::open(const QString &media)
{
	unloadMedia();

	/* Create a new libvlc media descriptor */
	_vlcMedia = libvlc_media_new_location(_vlcInstance, media.toAscii());
	VlcError::errmsg();
	qDebug() << "libvlc" <<"Media:" << media;

	_vlcCurrentMediaPlayer = libvlc_media_player_new_from_media(_vlcMedia);
	VlcError::errmsg();


	/* Disable mouse and keyboard events */
	libvlc_video_set_key_input(_vlcCurrentMediaPlayer, false);
	//libvlc_video_set_mouse_input(_vlcCurrentMediaPlayer, false);


	/* Get our media instance to use our window */
	if (_vlcCurrentMediaPlayer) {
#if defined(Q_WS_WIN)
		libvlc_media_player_set_hwnd(_vlcCurrentMediaPlayer, _widgetId);
#elif defined(Q_WS_MAC)
		libvlc_media_player_set_agl(_vlcCurrentMediaPlayer, _widgetId);
#else // Q_WS_X11
		libvlc_media_player_set_xwindow(_vlcCurrentMediaPlayer, _widgetId);
#endif // Q_WS_*

		VlcError::errmsg();
	}

	play();
}

void VlcMediaPlayer::unloadMedia()
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_media_player_release(_vlcCurrentMediaPlayer);
		_vlcCurrentMediaPlayer = NULL;
	}

	if (_vlcMedia) {
		libvlc_media_release(_vlcMedia);
		_vlcMedia = NULL;
	}

	VlcError::errmsg();
}

void VlcMediaPlayer::play()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	libvlc_media_player_play(_vlcCurrentMediaPlayer);
	VlcError::errmsg();
}

void VlcMediaPlayer::pause()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	if(libvlc_media_player_can_pause(_vlcCurrentMediaPlayer) == 1)
		libvlc_media_player_pause(_vlcCurrentMediaPlayer);
	VlcError::errmsg();
}

void VlcMediaPlayer::stop()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	libvlc_media_player_stop(_vlcCurrentMediaPlayer);
	unloadMedia();
	VlcError::errmsg();
}

void VlcMediaPlayer::checkPlayingState()
{
	if(_vlcCurrentMediaPlayer == NULL) {
		emit state(false, false, false);
		return;
	}

	bool playing;
	bool audio_count;
	bool video_count;

	playing = libvlc_media_player_get_state(_vlcCurrentMediaPlayer) == libvlc_Playing;
	audio_count = libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) > 0;
	video_count = libvlc_video_get_track_count(_vlcCurrentMediaPlayer) > 0;

	emit state(playing, audio_count, video_count);
}

bool VlcMediaPlayer::isActive()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return false;

	// It's possible that the vlc doesn't play anything
	// so check before
	libvlc_media_t *curMedia;
	curMedia = libvlc_media_player_get_media(_vlcCurrentMediaPlayer);

	if (curMedia == NULL)
		return false;

	libvlc_state_t state;
	state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer);

	if(state == libvlc_NothingSpecial || state == libvlc_Ended || state == libvlc_Error)
		return false;
	else
		return true;
}
