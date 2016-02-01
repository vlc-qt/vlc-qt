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

/* MSVC support fix */
#if defined(_MSC_VER)
#   include <BaseTsd.h>
    typedef SSIZE_T ssize_t;
#endif
/* MSVC + MinGW support fix */
#if defined (_WIN32)
#   define LIBVLC_USE_PTHREAD_CANCEL 1
#endif

#include <vlc/vlc.h>
#include <vlc/plugins/vlc_common.h>
#include <vlc/plugins/vlc_variables.h>

#include "core/Audio.h"
#include "core/Error.h"
#include "core/MediaPlayer.h"

/*!
    \private
*/
class VlcAudioCallbackHelper
{
public:
    static int volumeCallback(vlc_object_t *obj,
                              const char *name,
                              vlc_value_t oldVal,
                              vlc_value_t newVal,
                              void *data)
    {
        Q_UNUSED(obj)
        Q_UNUSED(name)
        Q_UNUSED(oldVal)

        VlcAudio *core = (VlcAudio *)data;
        emit core->volumeChangedF(newVal.f_float);
        int vol = newVal.f_float < 0 ? -1 : qRound(newVal.f_float * 100.f);
        emit core->volumeChanged(vol);
        return VLC_SUCCESS;
    }

    static int muteCallback(vlc_object_t *obj,
                            const char *name,
                            vlc_value_t oldVal,
                            vlc_value_t newVal,
                            void *data)
    {
        Q_UNUSED(obj);
        Q_UNUSED(name);
        Q_UNUSED(oldVal);

        VlcAudio *core = (VlcAudio *)data;
        emit core->muteChanged(newVal.b_bool);
        return VLC_SUCCESS;
    }
};

VlcAudio::VlcAudio(VlcMediaPlayer *player)
    : QObject(player),
      _vlcMediaPlayer(player->core())
{
    var_AddCallback((vlc_object_t *)_vlcMediaPlayer, "volume", VlcAudioCallbackHelper::volumeCallback, this);
    var_AddCallback((vlc_object_t *)_vlcMediaPlayer, "mute", VlcAudioCallbackHelper::muteCallback, this);
}

VlcAudio::~VlcAudio()
{
    var_DelCallback((vlc_object_t *)_vlcMediaPlayer, "volume", VlcAudioCallbackHelper::volumeCallback, this);
    var_DelCallback((vlc_object_t *)_vlcMediaPlayer, "mute", VlcAudioCallbackHelper::muteCallback, this);
}

bool VlcAudio::getMute() const
{
    bool mute = false;
    if (_vlcMediaPlayer) {
        mute = libvlc_audio_get_mute(_vlcMediaPlayer);
        VlcError::showErrmsg();
    }

    return mute;
}

void VlcAudio::setVolume(int volume)
{
    if (_vlcMediaPlayer) {
        // Don't change if volume is the same
        if (volume != VlcAudio::volume()) {
            libvlc_audio_set_volume(_vlcMediaPlayer, volume);
            VlcError::showErrmsg();
        }
    }
}

void VlcAudio::setTrack(int track)
{
    if (_vlcMediaPlayer) {
        libvlc_audio_set_track(_vlcMediaPlayer, track);
        VlcError::showErrmsg();
    }
}

bool VlcAudio::toggleMute() const
{
    if (_vlcMediaPlayer) {
        libvlc_audio_toggle_mute(_vlcMediaPlayer);
        VlcError::showErrmsg();
    }

    return getMute();
}

void VlcAudio::setMute(bool mute) const
{
    if (_vlcMediaPlayer && mute != getMute()) {
        libvlc_audio_set_mute(_vlcMediaPlayer, mute);
        VlcError::showErrmsg();
    }
}

int VlcAudio::track() const
{
    int track = -1;
    if (_vlcMediaPlayer) {
        track = libvlc_audio_get_track(_vlcMediaPlayer);
        VlcError::showErrmsg();
    }

    return track;
}

int VlcAudio::trackCount() const
{
    int count = -1;
    if (_vlcMediaPlayer) {
        count = libvlc_audio_get_track_count(_vlcMediaPlayer);
        VlcError::showErrmsg();
    }

    return count;
}

QStringList VlcAudio::trackDescription() const
{
    QStringList descriptions;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc;
        desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        VlcError::showErrmsg();

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
        VlcError::showErrmsg();

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

QMap<int, QString> VlcAudio::tracks() const
{
    QMap<int, QString> tracks;

    if (_vlcMediaPlayer) {
        libvlc_track_description_t *desc, *first;
        first = desc = libvlc_audio_get_track_description(_vlcMediaPlayer);
        VlcError::showErrmsg();

        if(desc != NULL)
        {
            tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
            if (trackCount() > 1) {
                for(int i = 1; i < trackCount(); i++) {
                    desc = desc->p_next;
                    tracks.insert(desc->i_id, QString().fromUtf8(desc->psz_name));
                }
            }
            libvlc_track_description_list_release(first);
        }
    }

    return tracks;
}

int VlcAudio::volume() const
{
    int volume = -1;
    if (_vlcMediaPlayer) {
        volume = libvlc_audio_get_volume(_vlcMediaPlayer);
        VlcError::showErrmsg();
    }

    return volume;
}

Vlc::AudioChannel VlcAudio::channel() const
{
    Vlc::AudioChannel channel = Vlc::AudioChannelError;
    if (_vlcMediaPlayer) {
        channel = Vlc::AudioChannel(libvlc_audio_get_channel(_vlcMediaPlayer));
        VlcError::showErrmsg();
    }

    return channel;
}

void VlcAudio::setChannel(Vlc::AudioChannel channel)
{
    if (_vlcMediaPlayer) {
        // Don't change if channel is the same
        if (channel != VlcAudio::channel()) {
            libvlc_audio_set_channel(_vlcMediaPlayer, channel);
            VlcError::showErrmsg();
        }
    }
}
