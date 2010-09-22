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
	bool mute = false;
	if(_vlcCurrentMediaPlayer) {
		mute = libvlc_audio_get_mute(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return mute;
}

void VlcAudio::setVolume(const int &volume)
{
	if(_vlcCurrentMediaPlayer) {
		// Don't change if volume is the same
		if(volume != VlcAudio::volume()) {
			libvlc_audio_set_volume(_vlcCurrentMediaPlayer, volume);
			VlcError::errmsg();
		}
	}
}

void VlcAudio::setTrack(const int &track)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_audio_set_track(_vlcCurrentMediaPlayer, track);
		VlcError::errmsg();
	}
}

bool VlcAudio::toggleMute()
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_audio_toggle_mute(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return getMute();
}

int VlcAudio::track()
{
	int track = -1;
	if(_vlcCurrentMediaPlayer) {
		track = libvlc_audio_get_track(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return track;
}

int VlcAudio::trackCount()
{
	int count = -1;
	if(_vlcCurrentMediaPlayer) {
		count = libvlc_audio_get_track_count(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return count;
}

QStringList VlcAudio::trackDescription()
{
	QStringList descriptions;

	if(_vlcCurrentMediaPlayer) {
		libvlc_track_description_t *desc;
		desc = libvlc_audio_get_track_description(_vlcCurrentMediaPlayer);
		VlcError::errmsg();

		descriptions << QString().fromUtf8(desc->psz_name);
		if(trackCount() > 1) {
			for(int i = 1; i < trackCount(); i++) {
				desc = desc->p_next;
				descriptions << QString().fromUtf8(desc->psz_name);
			}
		}
	}

	return descriptions;
}

int VlcAudio::volume()
{
	int volume = -1;
	if(_vlcCurrentMediaPlayer) {
		libvlc_audio_get_volume(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return volume;
}
