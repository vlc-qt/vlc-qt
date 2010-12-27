/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>

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
