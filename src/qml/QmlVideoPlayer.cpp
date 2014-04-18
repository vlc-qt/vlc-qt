/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "qml/QmlVideoPlayer.h"

VlcQmlVideoPlayer::VlcQmlVideoPlayer(QQuickItem *parent)
    : VlcQmlVideoObject(parent),
      _instance(0),
      _player(0),
      _media(0),
      _audioManager(0),
      _hasMedia(false),
      _autoplay(true)
{
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);
    _audioManager = new VlcAudio(_player);
}

VlcQmlVideoPlayer::~VlcQmlVideoPlayer()
{
    _player->stop();

    delete _audioManager;
    delete _media;
    delete _player;
    delete _instance;
}

void VlcQmlVideoPlayer::close()
{
    _hasMedia = false;

    _player->stop();
}

void VlcQmlVideoPlayer::openFile(const QString &file)
{
    if (_media)
        delete _media;

    _media = new VlcMedia(file, true, _instance);

    openInternal();
}

void VlcQmlVideoPlayer::openStream(const QString &stream)
{
    if (_media)
        delete _media;

    _media = new VlcMedia(stream, false, _instance);

    openInternal();
}

void VlcQmlVideoPlayer::openInternal()
{
    if(_autoplay)
        _player->open(_media);
    else
        _player->openOnly(_media);

    connectToMediaPlayer(_player);

    _hasMedia = true;
}

bool VlcQmlVideoPlayer::autoplay() const
{
    return _autoplay;
}

void VlcQmlVideoPlayer::setAutoplay(bool autoplay)
{
    _autoplay = autoplay;
}

QUrl VlcQmlVideoPlayer::url() const
{
    if (_media)
        return QUrl( _media->currentLocation() );
    else
        return QUrl();
}

void VlcQmlVideoPlayer::setUrl(const QUrl &url)
{
    if (_media)
        delete _media;

    _media = new VlcMedia(url.toString(), url.isLocalFile(), _instance);

    openInternal();
}

void VlcQmlVideoPlayer::pause()
{
    _player->pause();
}

void VlcQmlVideoPlayer::play()
{
    _player->play();
}

void VlcQmlVideoPlayer::stop()
{
    _player->stop();
    disconnectFromMediaPlayer(_player);
}

int VlcQmlVideoPlayer::volume() const
{
    return _audioManager->volume();
}

void VlcQmlVideoPlayer::setVolume(int volume)
{
    _audioManager->setVolume(volume);
    emit volumeChanged();
}

int VlcQmlVideoPlayer::aspectRatio()
{
    return (int) VlcQmlVideoObject::aspectRatio();
}

void VlcQmlVideoPlayer::setAspectRatio(int aspectRatio)
{
    VlcQmlVideoObject::setAspectRatio( (Vlc::Ratio)aspectRatio );
}

int VlcQmlVideoPlayer::cropRatio()
{
    return (int) VlcQmlVideoObject::cropRatio();
}

void VlcQmlVideoPlayer::setCropRatio(int cropRatio)
{
    VlcQmlVideoObject::setCropRatio( (Vlc::Ratio)cropRatio );
}
