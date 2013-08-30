/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>

#include "core/Audio.h"
#include "core/Error.h"
#include "core/MediaPlayer.h"

VlcAudio::VlcAudio(VlcMediaPlayer *player)
    : QObject(player),
      _vlcMediaPlayer(player->core()) { }

VlcAudio::~VlcAudio() { }

bool VlcAudio::getMute() const
{
    bool mute = false;
    if (_vlcMediaPlayer) {
        mute = libvlc_audio_get_mute(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return mute;
}

void VlcAudio::setVolume(int volume)
{
    if (_vlcMediaPlayer) {
        // Don't change if volume is the same
        if (volume != VlcAudio::volume()) {
            libvlc_audio_set_volume(_vlcMediaPlayer, volume);
            VlcError::errmsg();
        }
    }
}

void VlcAudio::setTrack(int track)
{
    if (_vlcMediaPlayer) {
        libvlc_audio_set_track(_vlcMediaPlayer, track);
        VlcError::errmsg();
    }
}

bool VlcAudio::toggleMute() const
{
    if (_vlcMediaPlayer) {
        libvlc_audio_toggle_mute(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return getMute();
}

int VlcAudio::track() const
{
    int track = -1;
    if (_vlcMediaPlayer) {
        track = libvlc_audio_get_track(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return track;
}

int VlcAudio::trackCount() const
{
    int count = -1;
    if (_vlcMediaPlayer) {
        count = libvlc_audio_get_track_count(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return count;
}

QStringList VlcAudio::trackDescription() const
{
    QStringList descriptions;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        VlcError::errmsg();

        descriptions << QString().fromUtf8(desc->psz_name);
        if (trackCount() > 1) {
            for (int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                descriptions << QString().fromUtf8(desc->psz_name);
            }
        }
    }

    return descriptions;
}

QList<int> VlcAudio::trackIds() const
{
    QList<int> ids;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        VlcError::errmsg();

        ids << desc->i_id;
        if (trackCount() > 1) {
            for(int i = 1; i < trackCount(); i++) {
                desc = desc->p_next;
                ids << desc->i_id;
            }
        }
    }

    return ids;
}

int VlcAudio::volume() const
{
    int volume = -1;
    if (_vlcMediaPlayer) {
        volume = libvlc_audio_get_volume(_vlcMediaPlayer);
        VlcError::errmsg();
    }

    return volume;
}
