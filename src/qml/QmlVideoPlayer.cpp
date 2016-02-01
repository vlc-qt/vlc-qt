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
#include <QtQml/QQmlEngine>

#include "Config.h"

#include "core/Video.h"
#include "core/Audio.h"
#include "core/Common.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaPlayer.h"

#include "qml/QmlVideoPlayer.h"

VlcQmlVideoPlayer::VlcQmlVideoPlayer(QQuickItem *parent)
    : VlcQmlVideoObject(parent),
      _instance(0),
      _media(0),
      _audioManager(0),
      _deinterlacing(Vlc::Disabled),
      _hasMedia(false),
      _autoplay(true),
      _seekable(true)

{
    _instance = new VlcInstance(VlcCommon::args(), this);
    _instance->setUserAgent(qApp->applicationName(), qApp->applicationVersion());
    _player = new VlcMediaPlayer(_instance);
    _audioManager = new VlcAudio(_player);

    connect(_player, SIGNAL(stateChanged()), this, SIGNAL(stateChanged()));
    connect(_player, SIGNAL(seekableChanged(bool)), this, SLOT(seekableChangedPrivate(bool)));
    connect(_player, SIGNAL(lengthChanged(int)), this, SIGNAL(lengthChanged()));
    connect(_player, SIGNAL(timeChanged(int)), this, SIGNAL(timeChanged()));
    connect(_player, SIGNAL(positionChanged(float)), this, SIGNAL(positionChanged()));

    _audioTracksModel = new TracksModel(this);
}

VlcQmlVideoPlayer::~VlcQmlVideoPlayer()
{
    _player->stop();

    delete _audioManager;
    delete _media;
    delete _player;
    delete _instance;
}

void VlcQmlVideoPlayer::registerPlugin()
{
    qmlRegisterType<VlcQmlVideoPlayer>("VLCQt", LIBVLCQT_VERSION_QML_MAJOR, LIBVLCQT_VERSION_QML_MINOR, "VlcVideoPlayer");
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

TracksModel *VlcQmlVideoPlayer::audioTracksModel() const
{
    return _audioTracksModel;
}

int VlcQmlVideoPlayer::audioTrack() const
{
    return _audioManager->track();
}

void VlcQmlVideoPlayer::setAudioTrack(int audioTrack)
{
    _audioManager->setTrack(audioTrack);
    emit audioTrackChanged();
}

QString VlcQmlVideoPlayer::deinterlacing() const
{
    return Vlc::deinterlacing()[_deinterlacing];
}

void VlcQmlVideoPlayer::setDeinterlacing(const QString &deinterlacing)
{
    _deinterlacing = (Vlc::Deinterlacing) Vlc::deinterlacing().indexOf(deinterlacing);
    _player->video()->setDeinterlace(_deinterlacing);
}

int VlcQmlVideoPlayer::state() const
{
    return (int)_player->state();
}

bool VlcQmlVideoPlayer::seekable() const
{
    return _seekable;
}

int VlcQmlVideoPlayer::length() const
{
    return _player->length();
}

int VlcQmlVideoPlayer::time() const
{
    return _player->time();
}

void VlcQmlVideoPlayer::setTime(int time)
{
    _player->setTime( time );
}

float VlcQmlVideoPlayer::position() const
{
    return _player->position();
}

void VlcQmlVideoPlayer::setPosition(float position)
{
    _player->setPosition( position );
}

void VlcQmlVideoPlayer::seekableChangedPrivate(bool seekable)
{
    _seekable = seekable;
    emit seekableChanged();
}

void VlcQmlVideoPlayer::mediaParsed(int parsed)
{
    if(parsed == 1)
    {
        _audioTracksModel->clear();
        _audioTracksModel->load(_audioManager->tracks());

        setAudioTrack(_audioManager->track());
    }
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
        return QUrl(_media->currentLocation());
    else
        return QUrl();
}

void VlcQmlVideoPlayer::setUrl(const QUrl &url)
{
    _player->stop();

    if (_media)
        _media->deleteLater();

    if(url.isLocalFile()) {
        _media = new VlcMedia(url.toLocalFile(), true, _instance);
    } else {
        _media = new VlcMedia(url.toString(QUrl::FullyEncoded), false, _instance);
    }

    connect(_media, &VlcMedia::parsedChanged, this, &VlcQmlVideoPlayer::mediaParsed);

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

QString VlcQmlVideoPlayer::aspectRatio() const
{
    return Vlc::ratio()[VlcQmlVideoObject::aspectRatio()];
}

void VlcQmlVideoPlayer::setAspectRatio(const QString &aspectRatio)
{
    VlcQmlVideoObject::setAspectRatio( (Vlc::Ratio) Vlc::ratio().indexOf(aspectRatio) );
}

QString VlcQmlVideoPlayer::cropRatio() const
{
    return Vlc::ratio()[VlcQmlVideoObject::cropRatio()];
}

void VlcQmlVideoPlayer::setCropRatio(const QString &cropRatio)
{
    VlcQmlVideoObject::setCropRatio( (Vlc::Ratio) Vlc::ratio().indexOf(cropRatio) );
}
