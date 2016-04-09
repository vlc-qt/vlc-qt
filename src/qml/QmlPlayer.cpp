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

#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/MediaPlayer.h"
#include "core/Media.h"
#include "core/Video.h"

#include "qml/QmlPlayer.h"
#include "qml/QmlSource.h"

VlcQmlPlayer::VlcQmlPlayer(QObject *parent)
    : VlcQmlSource(parent),
      _media(0),
      _autoplay(true),
      _deinterlacing(Vlc::Disabled)
{
    _instance = new VlcInstance(VlcCommon::args(), this);
    _player = new VlcMediaPlayer(_instance);

    connect(_player, &VlcMediaPlayer::lengthChanged, this, &VlcQmlPlayer::lengthChanged);
    connect(_player, &VlcMediaPlayer::positionChanged, this, &VlcQmlPlayer::positionChanged);
    connect(_player, &VlcMediaPlayer::seekableChanged, this, &VlcQmlPlayer::seekableChanged);
    connect(_player, &VlcMediaPlayer::stateChanged, this, &VlcQmlPlayer::stateChanged);
    connect(_player, &VlcMediaPlayer::timeChanged, this, &VlcQmlPlayer::timeChanged);
    connect(_player, &VlcMediaPlayer::vout, this, &VlcQmlPlayer::mediaPlayerVout);

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

void VlcQmlPlayer::pause()
{
    _player->pause();
}

void VlcQmlPlayer::play()
{
    _player->play();
}

void VlcQmlPlayer::stop()
{
    _player->stop();
}

bool VlcQmlPlayer::autoplay() const
{
    return _autoplay;
}

void VlcQmlPlayer::setAutoplay(bool autoplay)
{
    if (_autoplay == autoplay)
        return;

    _autoplay = autoplay;
    emit autoplayChanged();
}

int VlcQmlPlayer::deinterlacing() const
{
    return _deinterlacing;
}

void VlcQmlPlayer::setDeinterlacing(int deinterlacing)
{
    if (_deinterlacing == deinterlacing)
        return;

    _deinterlacing = Vlc::Deinterlacing(deinterlacing);
    _player->video()->setDeinterlace(_deinterlacing);
    emit deinterlacingChanged();
}

qint64 VlcQmlPlayer::length() const
{
    return _player->length();
}

bool VlcQmlPlayer::seekable() const
{
    return _player->seekable();
}

int VlcQmlPlayer::state() const
{
    return _player->state();
}

float VlcQmlPlayer::position() const
{
    return _player->position();
}

void VlcQmlPlayer::setPosition(float position)
{
    _player->setPosition(position);
}

qint64 VlcQmlPlayer::time() const
{
    return _player->time();
}

void VlcQmlPlayer::setTime(qint64 time)
{
    _player->setTime(time);
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
    if (url == VlcQmlPlayer::url())
        return;

    _player->stop();

    if (_media)
        _media->deleteLater();

    if (url.isLocalFile()) {
        _media = new VlcMedia(url.toLocalFile(), true, _instance);
    } else {
        _media = new VlcMedia(url.toString(QUrl::FullyEncoded), false, _instance);
    }

    connect(_media, static_cast<void (VlcMedia::*)(bool)>(&VlcMedia::parsedChanged), this, &VlcQmlPlayer::mediaParsed);

    openInternal();

    emit urlChanged();
}

int VlcQmlPlayer::volume() const
{
    return _player->audio()->volume();
}

void VlcQmlPlayer::setVolume(int volume)
{
    if (volume == VlcQmlPlayer::volume())
        return;

    _player->audio()->setVolume(volume);
    emit volumeChanged();
}

void VlcQmlPlayer::mediaParsed(bool parsed)
{
    Q_UNUSED(parsed)
}

void VlcQmlPlayer::mediaPlayerVout(int)
{
}

void VlcQmlPlayer::openInternal()
{
    if (_autoplay)
        _player->open(_media);
    else
        _player->openOnly(_media);
}
