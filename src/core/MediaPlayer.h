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

#include <QWidget>

#include "Enums.h"

class VlcAudio;
class VlcInstance;
class VlcMedia;
class VlcVideo;
class VlcVideoWidget;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;
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
        \brief Get current media object
        \return media object (VlcMedia *)
    */
    VlcMedia *currentMedia();

    /*!
        \brief Get current media core object
        \return media core object (libvlc_media_t *)
    */
    libvlc_media_t *currentMediaCore();

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

    /*! \brief Set video widget.

        Set video widget to be able to play video inside Qt interface.

        \param widget video widget (VlcVideoWidget *)
    */
    void setVideoWidget(VlcVideoWidget *widget);

    /*!
        \brief Get video output status
        \return video output status (const bool)
    */
    bool hasVout() const;

    /*!
        \brief Get current player state.
        \return current player state (const Vlc::State)
    */
    Vlc::State state() const;

    /*!
        \brief Get current video widget.
        \return current video widget (VlcVideoWidget *)
    */
    VlcVideoWidget *videoWidget();


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
        \brief Signal sent when end reached
    */
    void end();

    /*!
        \brief Signal sent on error
    */
    void error();

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

    /*!
        \brief Signal sent when paused
    */
    void paused();

    /*!
        \brief Signal sent when playing
    */
    void playing();

    /*!
        \brief Signal sent on position change
        \param float position
    */
    void positionChanged(const float &);

    /*!
        \brief Signal sent when stopped
    */
    void stopped();

    /*!
        \brief Signal sent on time change
        \param int time
    */
    void timeChanged(const int &);

    /*!
        \brief Signal sent when video output is available
        \param int vout count
    */
    void vout(const int &);


private slots:
    void emitStatus();

private:
    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_player_t *_vlcMediaPlayer;
    libvlc_event_manager_t *_vlcMediaPlayerEvent;

    VlcMedia *_media;

    VlcAudio *_vlcAudio;
    VlcVideo *_vlcVideo;

    VlcVideoWidget *_videoWidget;
    WId _currentWId;

    QTimer *_check;
};

#endif // VLCQT_MEDIAPLAYER_H_
