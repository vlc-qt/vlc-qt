/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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
#include "gui/VideoWidget.h"

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

    _videoWidget = 0;

    _check = new QTimer(this);
    connect(_check, SIGNAL(timeout()), this, SLOT(emitStatus()));
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

void VlcMediaPlayer::emitStatus()
{
    Vlc::State s = state();
    bool audio_count;
    bool video_count;

    if (s == Vlc::Buffering ||
        s == Vlc::Playing ||
        s == Vlc::Paused) {
        audio_count = _vlcAudio->trackCount() > 0;
        video_count = _vlcVideo->trackCount() > 0;
    } else {
        audio_count = false;
        video_count = false;
    }

    VlcError::errmsg();

    emit currentState(s);
    emit hasAudio(audio_count);
    emit hasVideo(video_count);

    // Deprecated
    bool play = s == Vlc::Playing;
    bool buffering = s == Vlc::Buffering;
    emit playing(play, buffering);
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
    if (!_vlcMediaPlayer)
        return;

    WId id;
    if (_videoWidget)
        id = _videoWidget->request();
    else
        id = 0;

    /* Get our media instance to use our window */
#if defined(Q_WS_WIN)
    libvlc_media_player_set_hwnd(_vlcMediaPlayer, id);
#elif defined(Q_WS_MAC)
    libvlc_media_player_set_nsobject(_vlcMediaPlayer, (void *)id);
#elif defined(Q_WS_X11)
    libvlc_media_player_set_xwindow(_vlcMediaPlayer, id);
#endif

    libvlc_media_player_play(_vlcMediaPlayer);

    VlcError::errmsg();
}

void VlcMediaPlayer::pause()
{
    if (!_vlcMediaPlayer)
        return;

    if (libvlc_media_player_can_pause(_vlcMediaPlayer))
        libvlc_media_player_pause(_vlcMediaPlayer);

    VlcError::errmsg();
}

void VlcMediaPlayer::setTime(const int &time)
{
    libvlc_media_player_set_time(_vlcMediaPlayer, time);

    VlcError::errmsg();
}

void VlcMediaPlayer::setVideoWidget(VlcVideoWidget *widget)
{
    _videoWidget = widget;
}

Vlc::State VlcMediaPlayer::state() const
{
    // It's possible that the vlc doesn't play anything
    // so check before
    if (!libvlc_media_player_get_media(_vlcMediaPlayer))
        return Vlc::Idle;

    libvlc_state_t state;
    state = libvlc_media_player_get_state(_vlcMediaPlayer);

    VlcError::errmsg();

    return Vlc::State(state);
}

void VlcMediaPlayer::stop()
{
    if (!_vlcMediaPlayer)
        return;

    if (_videoWidget)
        _videoWidget->release();

    libvlc_media_player_stop(_vlcMediaPlayer);

    VlcError::errmsg();
}

int VlcMediaPlayer::time() const
{
    libvlc_time_t time = libvlc_media_player_get_time(_vlcMediaPlayer);

    VlcError::errmsg();

    return time;
}

VlcVideoWidget *VlcMediaPlayer::videoWidget()
{
    return _videoWidget;
}
