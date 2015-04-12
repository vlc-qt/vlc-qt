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

#ifndef VLCQT_MEDIAPLAYER_H_
#define VLCQT_MEDIAPLAYER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>

#include <QtGui/qwindowdefs.h>

#include "Config.h"
#include "Enums.h"
#include "SharedExportCore.h"

class VlcAudio;
class VlcEqualizer;
class VlcInstance;
class VlcMedia;
class VlcVideo;
class VlcVideoDelegate;

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
class VLCQT_CORE_EXPORT VlcMediaPlayer : public QObject
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
    libvlc_media_player_t *core() const;

    /*!
        \brief Returns audio manager object.
        \return audio manager (VlcAudio *)
    */
    VlcAudio *audio() const;

    /*!
        \brief Returns video manager object.
        \return video manager (VlcVideo *)
    */
    VlcVideo *video() const;

#if LIBVLC_VERSION >= 0x020200
    /*!
        \brief Returns equalizer object.
        \return equalizer (VlcEqualizer *)
    */
    VlcEqualizer *equalizer() const;
#endif

    /*!
        \brief Get the current movie length (in ms).
        \return the movie length (in ms), or -1 if there is no media (const int)
    */
    int length() const;

    /*!
        \brief Get current media object
        \return media object (VlcMedia *)
    */
    VlcMedia *currentMedia() const;

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

    /*!
        \brief Just opens the media file or stream, do not starts playing the media.
        \param media object (VlcMedia *)
    */
    void openOnly(VlcMedia *media);

public slots:
    /*! \brief Set the movie time (in ms).

        This has no effect if no media is being played. Not all formats and protocols support this.

        \param time the movie time (in ms) (int)
    */
    void setTime(int time);

public:
    /*!
        \brief Get the current movie time (in ms).
        \return the movie time (in ms), or -1 if there is no media (const int)
    */
    int time() const;

    /*! \brief Set video widget.

        Set video widget to be able to play video inside Qt interface.

        \param widget video widget (VlcVideoDelegate *)
    */
    void setVideoWidget(VlcVideoDelegate *widget);

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
    VlcVideoDelegate *videoWidget() const;

    /*!
        \brief Get current video position.
        \return current video position (float)
    */
    float position();

public slots:
    /*! \brief Set the movie position.

        This has no effect if no media is being played. Not all formats and protocols support this.

        \param pos the movie position (float)
    */
    void setPosition(float pos);

    /*!
        \brief Starts playing current media if possible
    */
    void play();

    /*!
        \brief Pauses the playback of current media if possible
    */
    void pause();

    /*!
        \brief Toggles pause of the playback of current media if possible
    */
    void togglePause();

    /*!
        \brief Resumes the playback of current media if possible
    */
    void resume();

    /*!
        \brief Stops playing current media
    */
    void stop();


signals:
    /*!
        \brief Signal sent on backward
    */
    void backward();

    /*!
        \brief Signal sent on buffering
        \param float buffer in percent
    */
    void buffering(float);

    /*!
        \brief Signal sent on buffering
        \param int buffer in percent
    */
    void buffering(int);

    /*!
        \brief Signal sent when end reached
    */
    void end();

    /*!
        \brief Signal sent on error
    */
    void error();

    /*!
        \brief Signal sent on forward
    */
    void forward();

    /*!
        \brief Signal sent on length change
        \param int length
    */
    void lengthChanged(int);

    /*!
        \brief Signal sent on media change
        \param libvlc_media_t * media
    */
    void mediaChanged(libvlc_media_t *);

    /*!
        \brief Signal sent nothing speciall happened
    */
    void nothingSpecial();

    /*!
        \brief Signal sent when opening
    */
    void opening();

    /*!
        \brief Signal sent on pausable change
        \param bool pausable
    */
    void pausableChanged(bool);

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
    void positionChanged(float);

    /*!
        \brief Signal sent on seekable change
        \param bool seekable
    */
    void seekableChanged(bool);

    /*!
        \brief Signal sent on snapshot taken
        \param QString filename
    */
    void snapshotTaken(const QString &);

    /*!
        \brief Signal sent when stopped
    */
    void stopped();

    /*!
        \brief Signal sent on time change
        \param int time
    */
    void timeChanged(int);

    /*!
        \brief Signal sent on title change
        \param int title
    */
    void titleChanged(int);

    /*!
        \brief Signal sent when video output is available
        \param int vout count
    */
    void vout(int);

    /*!
        \brief Signal sent when state of the player changed
    */
    void stateChanged();

private:
    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_player_t *_vlcMediaPlayer;
    libvlc_event_manager_t *_vlcEvents;

    VlcMedia *_media;

    VlcAudio *_vlcAudio;
    VlcVideo *_vlcVideo;
#if LIBVLC_VERSION >= 0x020200
    VlcEqualizer *_vlcEqualizer;
#endif

    VlcVideoDelegate *_videoWidget;
    WId _currentWId;
};

#endif // VLCQT_MEDIAPLAYER_H_
