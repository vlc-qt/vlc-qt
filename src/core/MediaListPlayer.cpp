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

#include "core/Error.h"
#include "core/Instance.h"
#include "core/MediaList.h"
#include "core/MediaListPlayer.h"
#include "core/MediaPlayer.h"

VlcMediaListPlayer::VlcMediaListPlayer(VlcInstance *instance)
    : QObject(instance)
{
    _vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());

    VlcError::errmsg();
}

VlcMediaListPlayer::VlcMediaListPlayer(VlcMediaPlayer *player,
                                       VlcInstance *instance)
    : QObject(instance)
{
    _vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());
    setMediaPlayer(player);

    VlcError::errmsg();
}

VlcMediaListPlayer::~VlcMediaListPlayer()
{
    libvlc_media_list_player_release(_vlcMediaListPlayer);

    VlcError::errmsg();
}

libvlc_media_list_player_t *VlcMediaListPlayer::core()
{
    return _vlcMediaListPlayer;
}

void VlcMediaListPlayer::itemAt(const int &index)
{
    libvlc_media_list_player_play_item_at_index(_vlcMediaListPlayer, index);

    VlcError::errmsg();
}

void VlcMediaListPlayer::next()
{
    libvlc_media_list_player_next(_vlcMediaListPlayer);

    VlcError::errmsg();
}

void VlcMediaListPlayer::play()
{
    libvlc_media_list_player_play(_vlcMediaListPlayer);

    VlcError::errmsg();
}

void VlcMediaListPlayer::previous()
{
    libvlc_media_list_player_previous(_vlcMediaListPlayer);

    VlcError::errmsg();
}

void VlcMediaListPlayer::stop()
{
    libvlc_media_list_player_stop(_vlcMediaListPlayer);

    VlcError::errmsg();
}

void VlcMediaListPlayer::setMediaList(VlcMediaList *list)
{
    libvlc_media_list_player_set_media_list(_vlcMediaListPlayer, list->core());

    VlcError::errmsg();
}

void VlcMediaListPlayer::setMediaPlayer(VlcMediaPlayer *player)
{
    libvlc_media_list_player_set_media_player(_vlcMediaListPlayer, player->core());

    VlcError::errmsg();
}

void VlcMediaListPlayer::setPlaybackMode(const Vlc::PlaybackMode &mode)
{
    libvlc_media_list_player_set_playback_mode(_vlcMediaListPlayer, libvlc_playback_mode_t(mode));
}
