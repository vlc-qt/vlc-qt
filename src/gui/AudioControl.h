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

#ifndef VLCQT_AUDIOCONTROL_H_
#define VLCQT_AUDIOCONTROL_H_

#include <QtCore/QList>
#include <QtCore/QMap>

#include "Enums.h"
#include "SharedExport.h"

class QAction;
class QTimer;

class VlcAudio;
class VlcMediaPlayer;

/*!
    \class VlcAudioControl AudioControl.h vlc-qt/AudioControl.h
    \brief Audio control class

    This is one of VLC-Qt control classes.
    It provides audio tracks management.
*/
class VLCQT_EXPORT VlcAudioControl : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcAudioControl constructor
        \param player media player (VlcMediaPlayer *)
        \param language default audio language (QString)
        \param parent audio controller's parent object (QObject *)
    */
    explicit VlcAudioControl(VlcMediaPlayer *player,
                             const QString &language = 0,
                             QObject *parent = 0);

    /*!
        \brief AudioControl destructor
    */
    ~VlcAudioControl();


    /*!
        \brief Reset all settings and selected audio tracks.

        Usually called on media change.
    */
    void reset();

    /*!
        \brief Set default audio language
        \param language comma separated languages (QString)
    */
    void setDefaultAudioLanguage(const QString &language);


signals:
    /*!
        \brief Signal sending actions for changing audio tracks
        \param QList<QAction*> list of actions
        \param Vlc::ActionsType type of actions
    */
    void actions(QList<QAction *>,
                 const Vlc::ActionsType);

    /*!
        \brief Signal sending actions for changing audio tracks
        \param QList<QAction*> list of actions
    */
    void audioTracks(QList<QAction *>);


private slots:
    void clean();
    void update();
    void updateActions();

private:
    VlcAudio *_vlcAudio;
    VlcMediaPlayer *_vlcMediaPlayer;

    QTimer *_timer;

    QList<QAction *> _actionList;
    QMap<QString, int> _map;

    bool _manualLanguage;
    QStringList _preferedLanguage;
};

#endif // VLCQT_AUDIOCONTROL_H_
