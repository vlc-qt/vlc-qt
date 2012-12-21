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

#include <QtCore/QTimer>

#if defined(Qt5)
    #include <QtWidgets/QAction>
#elif defined(Qt4)
    #include <QtGui/QAction>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"

#include "widgets/ControlVideo.h"

VlcControlVideo::VlcControlVideo(VlcMediaPlayer *player,
                                 const QString &language,
                                 QObject *parent)
    : QObject(parent),
      _vlcMediaPlayer(player),
      _vlcVideo(player->video()),
      _actionSubList(QList<QAction *>()),
      _descSub(QMap<QString, int>()),
      _idSub(QMap<int, int>()),
      _actionVideoList(QList<QAction *>()),
      _descVideo(QMap<QString, int>()),
      _idVideo(QMap<int, int>()),
      _manualLanguage(false)
{
    if (!language.isNull() && !language.isEmpty())
        _preferedLanguage = language.split(" / ");

    _timerSubtitles = new QTimer(this);
    connect(_timerSubtitles, SIGNAL(timeout()), this, SLOT(updateSubtitleActions()));
    _timerVideo = new QTimer(this);
    connect(_timerVideo, SIGNAL(timeout()), this, SLOT(updateVideoActions()));

    _timerSubtitles->start(1000);
    _timerVideo->start(1000);
}

VlcControlVideo::~VlcControlVideo()
{
    delete _timerSubtitles;
    delete _timerVideo;
}

void VlcControlVideo::updateSubtitleActions()
{
    qDeleteAll(_actionSubList);
    _actionSubList.clear();
    _descSub.clear();
    _idSub.clear();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionSubList, Vlc::Subtitles);
        emit subtitleTracks(_actionSubList);
        return;
    }

    if (_vlcVideo->subtitleCount() > 0) {
        QStringList desc = _vlcVideo->subtitleDescription();
        QList<int> ids = _vlcVideo->subtitleIds();
        for (int i = 0; i < desc.size(); i++) {
            _descSub.insert(desc[i], ids[i]);
            _idSub.insert(ids[i], i);
            _actionSubList << new QAction(desc[i], this);
        }
    } else {
        emit actions(_actionSubList, Vlc::Subtitles);
        emit subtitleTracks(_actionSubList);
        _timerSubtitles->start(1000);
        return;
    }

    foreach (QAction *action, _actionSubList) {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(updateSubtitles()));

        if (!_manualLanguage) {
            foreach (const QString &language, _preferedLanguage) {
                if (action->text().contains(language, Qt::CaseInsensitive)) {
                    action->trigger();
                    _manualLanguage = true;
                }
            }
        }
    }

    _actionSubList[_idSub[_vlcVideo->subtitle()]]->setChecked(true);

    emit actions(_actionSubList, Vlc::Subtitles);
    emit subtitleTracks(_actionSubList);

    _timerSubtitles->start(60000);
}

void VlcControlVideo::updateSubtitles()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _descSub.value(action->text());

    _vlcVideo->setSubtitle(id);
}

void VlcControlVideo::loadSubtitle(const QString &subtitle)
{
    if (subtitle.isEmpty())
        return;

    _vlcVideo->setSubtitleFile(subtitle);

    _timerSubtitles->start(1000);
}

void VlcControlVideo::updateVideoActions()
{
    qDeleteAll(_actionVideoList);
    _actionVideoList.clear();
    _descVideo.clear();
    _idVideo.clear();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionVideoList, Vlc::VideoTrack);
        emit videoTracks(_actionVideoList);
        return;
    }

    if (_vlcVideo->trackCount() > 0) {
        QStringList desc = _vlcVideo->trackDescription();
        QList<int> ids = _vlcVideo->trackIds();
        for (int i = 0; i < desc.size(); i++) {
            _descVideo.insert(desc[i], ids[i]);
            _idVideo.insert(ids[i], i);
            _actionVideoList << new QAction(desc[i], this);
        }
    } else {
        emit actions(_actionVideoList, Vlc::VideoTrack);
        emit videoTracks(_actionVideoList);
        _timerVideo->start(1000);
        return;
    }

    foreach (QAction *action, _actionVideoList) {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(updateVideo()));
    }

    _actionVideoList[_idVideo[_vlcVideo->track()]]->setChecked(true);

    emit actions(_actionVideoList, Vlc::VideoTrack);
    emit videoTracks(_actionVideoList);

    _timerVideo->start(60000);
}

void VlcControlVideo::updateVideo()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _descVideo.value(action->text());

    _vlcVideo->setTrack(id);
}

void VlcControlVideo::reset()
{
    _timerSubtitles->start(1000);
    _timerVideo->start(1000);
    _manualLanguage = false;
}

void VlcControlVideo::setDefaultSubtitleLanguage(const QString &language)
{
    _preferedLanguage = language.split(" / ");
}
