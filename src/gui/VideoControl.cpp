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

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"
#include "gui/VideoControl.h"

VlcVideoControl::VlcVideoControl(const QString &language,
                                 QObject *parent)
    : QObject(parent),
    _actionSubList(QList<QAction *>()),
    _mapSub(QMap<QString, int>()),
    _actionVideoList(QList<QAction *>()),
    _mapVideo(QMap<QString, int>()),
    _manualLanguage(false)
{
    if(!language.isNull() && !language.isEmpty())
        _preferedLanguage = language.split(" / ");

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateSubtitleActions()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateVideoActions()));

    _timer->start(2000);
}

VlcVideoControl::~VlcVideoControl()
{
    delete _timer;

    for(int i = 0; i < _actionSubList.size(); i++)
        delete _actionSubList[i];
    for(int i = 0; i < _actionVideoList.size(); i++)
        delete _actionVideoList[i];
}

void VlcVideoControl::updateSubtitleActions() {
    for(int i = 0; i < _actionSubList.size(); i++)
        delete _actionSubList[i];
    _actionSubList.clear();
    _mapSub.clear();

    if(!VlcMediaPlayer::isActive()) {
        emit actions(_actionSubList, Vlc::Subtitles);
        emit subtitleTracks(_actionSubList);
        return;
    }

    if(VlcVideo::subtitleCount() > 0) {
        QStringList desc = VlcVideo::subtitleDescription();
        for(int i = 0; i < desc.size(); i++) {
            _mapSub.insert(desc[i], i);
            _actionSubList << new QAction(desc[i], this);
        }
    } else {
        emit actions(_actionSubList, Vlc::Subtitles);
        emit subtitleTracks(_actionSubList);
        return;
    }

    for (int i = 0; i < _actionSubList.size(); i++) {
        _actionSubList[i]->setCheckable(true);
        connect(_actionSubList[i], SIGNAL(triggered()), this, SLOT(updateSubtitles()));

        if(!_manualLanguage) {
            for(int j = 0; j < _preferedLanguage.size(); j++) {
                if(_actionSubList[i]->text().contains(_preferedLanguage[j], Qt::CaseInsensitive)) {
                    _actionSubList[i]->trigger();
                    _manualLanguage = true;
                }
            }
        }
    }

    _actionSubList[VlcVideo::subtitle()]->setChecked(true);

    emit actions(_actionSubList, Vlc::Subtitles);
    emit subtitleTracks(_actionSubList);

    _timer->start(60000);
}

void VlcVideoControl::updateSubtitles()
{
    int id = _mapSub.value(qobject_cast<QAction *>(sender())->text());

    VlcVideo::setSubtitle(id);
}

void VlcVideoControl::loadSubtitle(const QString &subtitle)
{
    if(subtitle.isEmpty())
        return;

    VlcVideo::setSubtitleFile(subtitle);

    _timer->start(1000);
}

void VlcVideoControl::updateVideoActions() {
    for(int i = 0; i < _actionVideoList.size(); i++)
        delete _actionVideoList[i];
    _actionVideoList.clear();
    _mapVideo.clear();

    if(!VlcMediaPlayer::isActive()) {
        emit actions(_actionVideoList, Vlc::VideoTrack);
        emit videoTracks(_actionVideoList);
        return;
    }

    if(VlcVideo::trackCount() > 0) {
        QStringList desc = VlcVideo::trackDescription();
        QList<int> ids = VlcVideo::trackIds();
        for(int i = 0; i < desc.size(); i++) {
            _mapVideo.insert(desc[i], ids[i]);
            _actionVideoList << new QAction(desc[i], this);
        }
    } else {
        emit actions(_actionVideoList, Vlc::VideoTrack);
        emit videoTracks(_actionVideoList);
        return;
    }

    for (int i = 0; i < _actionVideoList.size(); i++) {
        _actionVideoList[i]->setCheckable(true);
        connect(_actionVideoList[i], SIGNAL(triggered()), this, SLOT(updateVideo()));
    }

    _actionVideoList[VlcVideo::track()]->setChecked(true);

    emit actions(_actionVideoList, Vlc::VideoTrack);
    emit videoTracks(_actionVideoList);

    _timer->start(60000);
}

void VlcVideoControl::updateVideo()
{
    int id = _mapVideo.value(qobject_cast<QAction *>(sender())->text());

    VlcVideo::setTrack(id);
}

void VlcVideoControl::reset()
{
    _timer->start(2000);
    _manualLanguage = false;
}

void VlcVideoControl::setDefaultSubtitleLanguage(const QString &language)
{
    _preferedLanguage = language.split(" / ");
}
