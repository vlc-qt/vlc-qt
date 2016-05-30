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

#include <QtCore/QTimer>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QAction>
#else
#include <QtGui/QAction>
#endif

#include "core/Audio.h"
#include "core/MediaPlayer.h"

#include "widgets/ControlAudio.h"

VlcControlAudio::VlcControlAudio(VlcMediaPlayer *player,
                                 const QString &language,
                                 QObject *parent)
    : QObject(parent),
      _vlcAudio(player->audio()),
      _vlcMediaPlayer(player),
      _actionList(QList<QAction *>()),
      _desc(QMap<QString, int>()),
      _id(QMap<int, int>()),
      _manualLanguage(false)
{
    if (!language.isNull() && !language.isEmpty())
        _preferedLanguage = language.split(" / ");

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateActions()));

    _timer->start(1000);
}

VlcControlAudio::~VlcControlAudio()
{
    delete _timer;
}

void VlcControlAudio::clean()
{
    qDeleteAll(_actionList);
    _actionList.clear();
    _desc.clear();
    _id.clear();
}

void VlcControlAudio::reset()
{
    _timer->start(1000);
}

void VlcControlAudio::update()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    int id = _desc.value(action->text());

    _vlcAudio->setTrack(id);
}

void VlcControlAudio::updateActions()
{
    clean();

    if (!(_vlcMediaPlayer->state() == Vlc::Playing || _vlcMediaPlayer->state() == Vlc::Paused)) {
        emit actions(_actionList, Vlc::AudioTrack);
        emit audioTracks(_actionList);
        return;
    }

    if (_vlcAudio->trackCount() > 0) {
        QStringList desc = _vlcAudio->trackDescription();
        QList<int> ids = _vlcAudio->trackIds();
        for (int i = 0; i < desc.size(); i++) {
            _desc.insert(desc[i], ids[i]);
            _id.insert(ids[i], i);
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
            foreach (const QString &language, _preferedLanguage) {
                if (action->text().contains(language, Qt::CaseInsensitive)) {
                    action->trigger();
                    _manualLanguage = true;
                }
            }
        }
    }

    _actionList[_id[_vlcAudio->track()]]->setChecked(true);

    emit actions(_actionList, Vlc::AudioTrack);
    emit audioTracks(_actionList);

    _timer->start(60000);
}

void VlcControlAudio::setDefaultAudioLanguage(const QString &language)
{
    _preferedLanguage = language.split(" / ");
}
