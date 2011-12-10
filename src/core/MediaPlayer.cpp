/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
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

#include <vlc/vlc.h>

#include "core/Audio.h"
#include "core/Error.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"

VlcMediaPlayer::VlcMediaPlayer(VlcInstance *instance)
    : QObject(instance)
{
    _vlcMediaPlayer = libvlc_media_player_new(instance->core());

    /* Disable mouse and keyboard events */
    libvlc_video_set_key_input(_vlcMediaPlayer, false);
    libvlc_video_set_mouse_input(_vlcMediaPlayer, false);

    VlcError::errmsg();

    _vlcAudio = new VlcAudio(this);
    _vlcVideo = new VlcVideo(this);

    _check = new QTimer(this);
    connect(_check, SIGNAL(timeout()), this, SLOT(checkPlayingState()));
    _check->start(300);
}

VlcMediaPlayer::~VlcMediaPlayer()
{
    delete _check;

    delete _vlcAudio;
    delete _vlcVideo;

    libvlc_media_player_release(_vlcMediaPlayer);
}

libvlc_media_player_t *VlcMediaPlayer::core()
{
    return _vlcMediaPlayer;
}

VlcAudio *VlcMediaPlayer::audio()
{
    return _vlcAudio;
}

VlcVideo *VlcMediaPlayer::video()
{
    return _vlcVideo;
}

void VlcMediaPlayer::checkPlayingState()
{
    if(!isActive()) {
        emit playing(false, false);
        emit hasAudio(false);
        emit hasVideo(false);

        return;
    }

    bool play;
    bool buffering;
    bool audio_count;
    bool video_count;

    play = libvlc_media_player_get_state(_vlcMediaPlayer) == libvlc_Playing;
    buffering = libvlc_media_player_get_state(_vlcMediaPlayer) == libvlc_Buffering;
    audio_count = _vlcAudio->trackCount() > 0;
    video_count = _vlcVideo->trackCount() > 0;

    VlcError::errmsg();

    emit playing(play, buffering);
    emit hasAudio(audio_count);
    emit hasVideo(video_count);
}

bool VlcMediaPlayer::isActive() const
{
    // It's possible that the vlc doesn't play anything
    // so check before
    if (!libvlc_media_player_get_media(_vlcMediaPlayer))
        return false;

    libvlc_state_t state;
    state = libvlc_media_player_get_state(_vlcMediaPlayer);

    VlcError::errmsg();

    if(state == libvlc_NothingSpecial || state == libvlc_Stopped || state == libvlc_Ended || state == libvlc_Error)
        return false;
    else
        return true;
}

int VlcMediaPlayer::lenght() const
{
    libvlc_time_t lenght = libvlc_media_player_get_length(_vlcMediaPlayer);

    VlcError::errmsg();

    return lenght;
}

void VlcMediaPlayer::open(VlcMedia *media)
{
    libvlc_media_player_set_media(_vlcMediaPlayer, media->core());

    VlcError::errmsg();

    play();
}

void VlcMediaPlayer::play()
{
    if(!_vlcMediaPlayer)
        return;

    libvlc_media_player_play(_vlcMediaPlayer);

    VlcError::errmsg();
}

void VlcMediaPlayer::pause()
{
    if(!_vlcMediaPlayer)
        return;

    if(libvlc_media_player_can_pause(_vlcMediaPlayer) == 1)
        libvlc_media_player_pause(_vlcMediaPlayer);

    VlcError::errmsg();
}

void VlcMediaPlayer::setTime(const int &time)
{
    libvlc_media_player_set_time(_vlcMediaPlayer, time);

    VlcError::errmsg();
}

void VlcMediaPlayer::setVideoWidgetId(WindowId id)
{
    _widgetId = id;

    /* Get our media instance to use our window */
    if (_vlcMediaPlayer) {
#if defined(Q_WS_WIN)
        libvlc_media_player_set_hwnd(_vlcMediaPlayer, _widgetId);
#elif defined(Q_WS_MAC)
        libvlc_media_player_set_nsobject(_vlcMediaPlayer, _widgetId);
#else // Q_WS_X11
        libvlc_media_player_set_xwindow(_vlcMediaPlayer, _widgetId);
#endif // Q_WS_*

        VlcError::errmsg();
    }
}

void VlcMediaPlayer::stop()
{
    if(!_vlcMediaPlayer)
        return;

    libvlc_media_player_stop(_vlcMediaPlayer);

    VlcError::errmsg();
}

int VlcMediaPlayer::time() const
{
    libvlc_time_t time = libvlc_media_player_get_time(_vlcMediaPlayer);

    VlcError::errmsg();

    return time;
}

WindowId VlcMediaPlayer::videoWidgetId() const
{
    return _widgetId;
}
