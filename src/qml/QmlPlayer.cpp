/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#include "core/Common.h"
#include "core/Instance.h"
#include "core/MediaPlayer.h"
#include "core/Media.h"
#include "core/Video.h"

#include "qml/QmlPlayer.h"
#include "qml/QmlSource.h"

VlcQmlPlayer::VlcQmlPlayer(QObject *parent)
    : VlcQmlSource(parent),
      _media(0)
{
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _video = new VlcVideo(_player);

    setPlayer(_player);
}

VlcQmlPlayer::~VlcQmlPlayer()
{
    _player->stop();
    removePlayer();

    if (_media)
        delete _media;

    delete _player;
    delete _instance;
}

QUrl VlcQmlPlayer::url() const
{
    if (_media)
        return QUrl(_media->currentLocation());
    else
        return QUrl();
}

void VlcQmlPlayer::setUrl(const QUrl &url)
{
    _player->stop();

    if (_media)
        _media->deleteLater();

    if (url.isLocalFile()) {
        _media = new VlcMedia(url.toLocalFile(), true, _instance);
    } else {
        _media = new VlcMedia(url.toString(QUrl::FullyEncoded), false, _instance);
    }

    openInternal();

    emit urlChanged();
}

void VlcQmlPlayer::openInternal()
{
    _player->open(_media);
}
