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

#include <QtCore/QDebug>

#include <vlc/vlc.h>

#include "core/Error.h"
#include "core/Instance.h"
#include "core/MediaList.h"
#include "core/MediaListPlayer.h"
#include "core/MediaPlayer.h"

VlcMediaListPlayer::VlcMediaListPlayer(VlcInstance *instance)
    : QObject(instance),
      _list(0),
      _mode(Vlc::DefaultPlayback)
{
    _player = new VlcMediaPlayer(instance);

    _vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());
    _vlcEvents = libvlc_media_list_player_event_manager(_vlcMediaListPlayer);
    libvlc_media_list_player_set_media_player(_vlcMediaListPlayer, _player->core());

    createCoreConnections();

    VlcError::showErrmsg();
}

VlcMediaListPlayer::VlcMediaListPlayer(VlcMediaPlayer *player,
                                       VlcInstance *instance)
    : QObject(instance),
      _list(0),
      _mode(Vlc::DefaultPlayback)
{
    _player = player;

    _vlcMediaListPlayer = libvlc_media_list_player_new(instance->core());
    _vlcEvents = libvlc_media_list_player_event_manager(_vlcMediaListPlayer);
    libvlc_media_list_player_set_media_player(_vlcMediaListPlayer, _player->core());

    createCoreConnections();

    VlcError::showErrmsg();
}

VlcMediaListPlayer::~VlcMediaListPlayer()
{
    removeCoreConnections();

    libvlc_media_list_player_release(_vlcMediaListPlayer);

    VlcError::showErrmsg();
}

libvlc_media_list_player_t *VlcMediaListPlayer::core()
{
    return _vlcMediaListPlayer;
}

VlcMediaList *VlcMediaListPlayer::currentMediaList()
{
    return _list;
}

VlcMediaPlayer *VlcMediaListPlayer::mediaPlayer()
{
    return _player;
}

void VlcMediaListPlayer::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListPlayerPlayed
         << libvlc_MediaListPlayerNextItemSet
         << libvlc_MediaListPlayerStopped;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_attach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMediaListPlayer::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListPlayerPlayed
         << libvlc_MediaListPlayerNextItemSet
         << libvlc_MediaListPlayerStopped;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_detach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMediaListPlayer::itemAt(int index)
{
    libvlc_media_list_player_play_item_at_index(_vlcMediaListPlayer, index);

    VlcError::showErrmsg();
}

void VlcMediaListPlayer::next()
{
    libvlc_media_list_player_next(_vlcMediaListPlayer);

    VlcError::showErrmsg();
}

void VlcMediaListPlayer::play()
{
    libvlc_media_list_player_play(_vlcMediaListPlayer);

    VlcError::showErrmsg();
}

Vlc::PlaybackMode VlcMediaListPlayer::playbackMode() const
{
    return _mode;
}

void VlcMediaListPlayer::previous()
{
    libvlc_media_list_player_previous(_vlcMediaListPlayer);

    VlcError::showErrmsg();
}

void VlcMediaListPlayer::stop()
{
    libvlc_media_list_player_stop(_vlcMediaListPlayer);

    VlcError::showErrmsg();
}

void VlcMediaListPlayer::setMediaList(VlcMediaList *list)
{
    _list = list;
    libvlc_media_list_player_set_media_list(_vlcMediaListPlayer, list->core());

    VlcError::showErrmsg();
}

void VlcMediaListPlayer::setPlaybackMode(const Vlc::PlaybackMode &mode)
{
    _mode = mode;
    libvlc_media_list_player_set_playback_mode(_vlcMediaListPlayer, libvlc_playback_mode_t(mode));
}

void VlcMediaListPlayer::libvlc_callback(const libvlc_event_t *event,
                                         void *data)
{
    VlcMediaListPlayer *core = static_cast<VlcMediaListPlayer *>(data);

    switch(event->type)
    {
    case libvlc_MediaListPlayerPlayed:
        emit core->played();
        break;
    case libvlc_MediaListPlayerNextItemSet:
        emit core->nextItemSet(event->u.media_list_player_next_item_set.item);
        emit core->nextItemSet(core->currentMediaList()->at(core->currentMediaList()->indexOf(event->u.media_list_player_next_item_set.item)));
        break;
    case libvlc_MediaListPlayerStopped:
        emit core->stopped();
        break;
    default:
        break; // LCOV_EXCL_LINE
    }
}
