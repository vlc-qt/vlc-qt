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

#include "core/Audio.h"
#include "core/MediaPlayer.h"
#include "gui/AudioControl.h"

VlcAudioControl::VlcAudioControl(VlcMediaPlayer *player,
                                 const QString &language,
                                 QObject *parent)
    : QObject(parent),
      _vlcAudio(player->audio()),
      _vlcMediaPlayer(player),
      _actionList(QList<QAction *>()),
      _map(QMap<QString, int>()),
      _manualLanguage(false)
{
    if (!language.isNull() && !language.isEmpty())
        _preferedLanguage = language.split(" / ");

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateActions()));

    _timer->start(1000);
}


VlcAudioControl::~VlcAudioControl()
{
    delete _timer;
}

void VlcAudioControl::clean()
{
    qDeleteAll(_actionList);
    _actionList.clear();
    _map.clear();
}

void VlcAudioControl::reset()
{
    _timer->start(1000);
}

void VlcAudioControl::update()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _map.value(action->text());

    _vlcAudio->setTrack(id);
}

void VlcAudioControl::updateActions()
{
    clean();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionList, Vlc::AudioTrack);
        emit audioTracks(_actionList);
        return;
    }

    if (_vlcAudio->trackCount() > 0) {
        QStringList desc = _vlcAudio->trackDescription();
        for (int i = 0; i < desc.size(); i++) {
            _map.insert(desc[i], i);
            _actionList << new QAction(desc[i], this);
        }
    } else {
        emit actions(_actionList, Vlc::AudioTrack);
        emit audioTracks(_actionList);
        _timer->start(1000);
        return;
    }

    foreach (QAction *action, _actionList) {
        action->setCheckable(true);
        connect(action, SIGNAL(triggered()), this, SLOT(update()));

        if (!_manualLanguage) {
            foreach (QString language, _preferedLanguage) {
                if (action->text().contains(language, Qt::CaseInsensitive)) {
                    action->trigger();
                    _manualLanguage = true;
                }
            }
        }
    }

    _actionList[_vlcAudio->track()]->setChecked(true);

    emit actions(_actionList, Vlc::AudioTrack);
    emit audioTracks(_actionList);

    _timer->start(60000);
}

void VlcAudioControl::setDefaultAudioLanguage(const QString &language)
{
    _preferedLanguage = language.split(" / ");
}
