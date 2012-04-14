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

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "gui/VideoControl.h"

VlcVideoControl::VlcVideoControl(VlcMediaPlayer *player,
                                 const QString &language,
                                 QObject *parent)
    : QObject(parent),
      _vlcMediaPlayer(player),
      _vlcVideo(player->video()),
      _actionSubList(QList<QAction *>()),
      _mapSub(QMap<QString, int>()),
      _actionVideoList(QList<QAction *>()),
      _mapVideo(QMap<QString, int>()),
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

VlcVideoControl::~VlcVideoControl()
{
    delete _timerSubtitles;
    delete _timerVideo;
}

void VlcVideoControl::updateSubtitleActions() {
    qDeleteAll(_actionSubList);
    _actionSubList.clear();
    _mapSub.clear();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionSubList, Vlc::Subtitles);
        emit subtitleTracks(_actionSubList);
        return;
    }

    if (_vlcVideo->subtitleCount() > 0) {
        QStringList desc = _vlcVideo->subtitleDescription();
        for (int i = 0; i < desc.size(); i++) {
            _mapSub.insert(desc[i], i);
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
            foreach (QString language, _preferedLanguage) {
                if (action->text().contains(language, Qt::CaseInsensitive)) {
                    action->trigger();
                    _manualLanguage = true;
                }
            }
        }
    }

    _actionSubList[_vlcVideo->subtitle()]->setChecked(true);

    emit actions(_actionSubList, Vlc::Subtitles);
    emit subtitleTracks(_actionSubList);

    _timerSubtitles->start(60000);
}

void VlcVideoControl::updateSubtitles()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _mapSub.value(action->text());

    _vlcVideo->setSubtitle(id);
}

void VlcVideoControl::loadSubtitle(const QString &subtitle)
{
    if (subtitle.isEmpty())
        return;

    _vlcVideo->setSubtitleFile(subtitle);

    _timerSubtitles->start(1000);
}

void VlcVideoControl::updateVideoActions() {
    qDeleteAll(_actionVideoList);
    _actionVideoList.clear();
    _mapVideo.clear();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionVideoList, Vlc::VideoTrack);
        emit videoTracks(_actionVideoList);
        return;
    }

    if (_vlcVideo->trackCount() > 0) {
        QStringList desc = _vlcVideo->trackDescription();
        QList<int> ids = _vlcVideo->trackIds();
        for (int i = 0; i < desc.size(); i++) {
            _mapVideo.insert(desc[i], ids[i]);
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

    _actionVideoList[_vlcVideo->track()]->setChecked(true);

    emit actions(_actionVideoList, Vlc::VideoTrack);
    emit videoTracks(_actionVideoList);

    _timerVideo->start(60000);
}

void VlcVideoControl::updateVideo()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _mapVideo.value(action->text());

    _vlcVideo->setTrack(id);
}

void VlcVideoControl::reset()
{
    _timerSubtitles->start(1000);
    _timerVideo->start(1000);
    _manualLanguage = false;
}

void VlcVideoControl::setDefaultSubtitleLanguage(const QString &language)
{
    _preferedLanguage = language.split(" / ");
}
