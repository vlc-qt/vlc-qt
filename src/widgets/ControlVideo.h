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

#ifndef VLCQT_CONTROLVIDEO_H_
#define VLCQT_CONTROLVIDEO_H_

#include <QtCore/QList>
#include <QtCore/QMap>

#include "Enums.h"
#include "SharedExportWidgets.h"

class QAction;
class QTimer;

class VlcMediaPlayer;
class VlcVideo;

/*!
    \class VlcControlVideo ControlVideo.h vlc-qt/ControlVideo.h
    \brief Video control class

    This is one of VLC-Qt control classes.
    It provides video and subtitle tracks management.
*/
class VLCQT_WIDGETS_EXPORT VlcControlVideo : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VideoControl constructor
        \param player media player (VlcMediaPlayer *)
        \param language default subtitle language (QString)
        \param parent video controller's parent object (QObject)
    */
    explicit VlcControlVideo(VlcMediaPlayer *player,
                             const QString &language = 0,
                             QObject *parent = 0);

    /*!
        \brief VideoControl destructor
    */
    ~VlcControlVideo();


    /*!
        \brief Reset all settings and selected video and subtitle tracks

        Usually called on media change.
    */
    void reset();

    /*!
        \brief Set default subtitle language
        \param language comma separated languages (QString)
    */
    void setDefaultSubtitleLanguage(const QString &language);


public slots:
    /*!
        \brief Open and load subtitles from file
        \param subtitle full path to subtitles file
    */
    void loadSubtitle(const QString &subtitle);


signals:
    /*!
        \brief Signal sending actions for changing video and subititle tracks
        \param QList<QAction*> list of actions
        \param Vlc::ActionsType type of actions
    */
    void actions(QList<QAction *>,
                 const Vlc::ActionsType);

    /*!
        \brief Signal sending actions for changing subititle tracks
        \param Vlc::ActionsType type of actions
        \param QList<QAction*> list of actions
    */
    void subtitleTracks(QList<QAction *>);

    /*!
        \brief Signal sending actions for changing video tracks
        \param Vlc::ActionsType type of actions
        \param QList<QAction*> list of actions
    */
    void videoTracks(QList<QAction *>);


private slots:
    void updateSubtitleActions();
    void updateSubtitles();
    void updateVideoActions();
    void updateVideo();

private:
    VlcMediaPlayer *_vlcMediaPlayer;
    VlcVideo *_vlcVideo;

    QTimer *_timerSubtitles;
    QTimer *_timerVideo;

    QList<QAction *> _actionSubList;
    QMap<QString, int> _descSub;
    QMap<int, int> _idSub;

    QList<QAction *> _actionVideoList;
    QMap<QString, int> _descVideo;
    QMap<int, int> _idVideo;

    bool _manualLanguage;
    QStringList _preferedLanguage;
};

#endif // VLCQT_CONTROLVIDEO_H_
