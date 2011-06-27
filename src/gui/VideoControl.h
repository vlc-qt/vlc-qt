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

#ifndef VLCQT_VIDEOCONTROL_H_
#define VLCQT_VIDEOCONTROL_H_

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtGui/QAction>

#include "Enums.h"

/*!
    \class VlcVideoControl VideoControl.h vlc-qt/VideoControl.h
    \brief Video control class

    This is one of VLC-Qt control classes.
    It provides video and subtitle tracks management.
*/
class VlcVideoControl : public QObject
{
Q_OBJECT
public:
    /*!
        VideoControl constructor
        \param language default subtitle language (QString)
        \param parent video controller's parent object (QObject)
    */
    VlcVideoControl(const QString &language = 0,
                    QObject *parent = 0);

    /*!
        VideoControl destructor
    */
    ~VlcVideoControl();


    /*!
        Reset all settings and selected video and subtitle tracks
        Usually called on media change.
    */
    void reset();

    /*!
        Set default subtitle language
        \param language comma separated languages (QString)
    */
    void setDefaultSubtitleLanguage(const QString &language);


public slots:
    /*!
        Open and load subtitles from file
        \param subtitle full path to subtitles file
    */
    void loadSubtitle(const QString &subtitle);


signals:
    /*!
        Signal sending actions for changing video and subititle tracks
        \param QList<QAction*> list of actions
        \param Vlc::ActionsType type of actions
    */
    void actions(QList<QAction *>,
                 const Vlc::ActionsType);

    /*!
        Signal sending actions for changing subititle tracks
        \param Vlc::ActionsType type of actions
        \param QList<QAction*> list of actions
    */
    void subtitleTracks(QList<QAction *>);

    /*!
        Signal sending actions for changing video tracks
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
    QTimer *_timer;

    QList<QAction *> _actionSubList;
    QMap<QString, int> _mapSub;

    QList<QAction *> _actionVideoList;
    QMap<QString, int> _mapVideo;

    bool _manualLanguage;
    QStringList _preferedLanguage;
};

#endif // VLCQT_VIDEOCONTROL_H_
