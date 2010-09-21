/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Audio.cpp: libvlc audio controls
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
#include "core/Error.h"
#include "core/MediaPlayer.h"

bool VlcAudio::getMute()
{
	bool mute = libvlc_audio_get_mute(_vlcCurrentMediaPlayer);
	VlcError::errmsg();

	return mute;
}

void VlcAudio::setVolume(const int &volume)
{
	// No use, if media is not playing
	if(!VlcMediaPlayer::isActive())
		return;

	// Don't change if volume is the same
	if(volume != VlcAudio::volume()) {
		libvlc_audio_set_volume(_vlcCurrentMediaPlayer, volume);
		VlcError::errmsg();
	}
}

bool VlcAudio::toggleMute()
{
	libvlc_audio_toggle_mute(_vlcCurrentMediaPlayer);
	VlcError::errmsg();

	return getMute();
}

int VlcAudio::volume()
{
	// No use, if media is not playing
	if(!VlcMediaPlayer::isActive())
		return -1;

	int volume = libvlc_audio_get_volume(_vlcCurrentMediaPlayer);
	VlcError::errmsg();

	return volume;
}
