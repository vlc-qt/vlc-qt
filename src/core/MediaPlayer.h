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

#ifndef VLCQT_MEDIAPLAYER_H_
#define VLCQT_MEDIAPLAYER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

#include "Enums.h"

class VlcAudio;
class VlcInstance;
class VlcMedia;
class VlcVideo;

struct libvlc_media_player_t;

/*!
    \class VlcMediaPlayer MediaPlayer.h vlc-qt/MediaPlayer.h
    \brief Media Player

    A basic MediaPlayer manager for VLC-Qt library.
    It provides main playback controls.
*/
class VlcMediaPlayer : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcMediaPlayer constructor.

        This is mandatory to use libvlc playback functions.

        \param instance instance object (VlcInstance *)
    */
    explicit VlcMediaPlayer(VlcInstance *instance);

    /*!
        VlcMediaPlayer destructor
    */
    ~VlcMediaPlayer();

    /*!
        \brief Returns libvlc media player object.
        \return libvlc media player (libvlc_media_player_t *)
    */
    libvlc_media_player_t *core();

    /*!
        \brief Returns audio manager object.
        \return audio manager (VlcAudio *)
    */
    VlcAudio *audio();

    /*!
        \brief Returns video manager object.
        \return video manager (VlcVideo *)
    */
    VlcVideo *video();

    /*!
        \brief Get the current movie lenght (in ms).
        \return the movie lenght (in ms), or -1 if there is no media (const int)
    */
    int lenght() const;

    /*!
        \brief Open media file or stream. Any media should be playable and opened.
        \param media object (VlcMedia *)
    */
    void open(VlcMedia *media);

    /*! \brief Set the movie time (in ms).

        This has no effect if no media is being played. Not all formats and protocols support this.

        \param time the movie time (in ms) (int)
    */
    void setTime(const int &time);

    /*!
        \brief Get the current movie time (in ms).
        \return the movie time (in ms), or -1 if there is no media (const int)
    */
    int time() const;

    /*! \brief Set video widget ID.

        Set video widget ID to be able to play video inside Qt interface.

        \param id video widget ID (WId)
    */
    void setVideoWidgetId(const WId &id);

    /*!
        \brief Get current player state.
        \return current player state (const Vlc::State)
    */
    Vlc::State state() const;

    /*!
        \brief Get current video widget ID.
        \return current video widget ID (const WId)
    */
    WId videoWidgetId() const;


public slots:
    /*!
        \brief Starts playing current media if possible
    */
    void play();

    /*!
        \brief Pauses the playback of current media if possible
    */
    void pause();

    /*!
        \brief Stops playing current media
    */
    void stop();


signals:
    /*!
        \brief Signal for sending current state
        \param Vlc::State current player state
    */
    void currentState(const Vlc::State &);

    /*!
        \deprecated
        \brief Signal sending VLC-Qt playing and buffering status
        \param bool true if player is playing any media
        \param bool true if player is buffering
    */
    void playing(const bool &,
                 const bool &);

    /*!
        \brief Signal sending VLC-Qt audio status
        \param bool true if media has audio
    */
    void hasAudio(const bool &);

    /*!
        \brief Signal sending VLC-Qt video status
        \param bool true if media has video
    */
    void hasVideo(const bool &);


private slots:
    void emitStatus();

private:
    libvlc_media_player_t *_vlcMediaPlayer;

    VlcAudio *_vlcAudio;
    VlcVideo *_vlcVideo;

    WId _widgetId;

    QTimer *_check;
};

#endif // VLCQT_MEDIAPLAYER_H_
