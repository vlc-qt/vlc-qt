/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_QMLPLAYER_H_
#define VLCQT_QMLPLAYER_H_

#include <QtCore/QUrl>

#include <VLCQtCore/Enums.h>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

#include "QmlSource.h"

/*!
    \class VlcQmlPlayer QmlPlayer.h VLCQtQml/QmlPlayer.h
    \ingroup VLCQtQml
    \brief QML player

    A QML media player that can play multimedia files inside QML interface.
    You need VlcQmlVideoOutput to display video.

    \see VlcQmlVideoOutput
 */
class VlcQmlPlayer : public VlcQmlSource
{
    Q_OBJECT

    /*!
        \brief Current autoplay setting
        \see autoplay
        \see setAutoplay
        \see autoplayChanged
     */
    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay NOTIFY autoplayChanged)

    /*!
        \brief Current deinterlacing mode
        \see deinterlacing
        \see setDeinterlacing
        \see deinterlacingChanged
     */
    Q_PROPERTY(int deinterlacing READ deinterlacing WRITE setDeinterlacing NOTIFY deinterlacingChanged)

    /*!
        \brief Current media length
        \see length
        \see lengthChanged
     */
    Q_PROPERTY(qint64 length READ length NOTIFY lengthChanged)

    /*!
        \brief Current media position
        \see position
        \see setPosition;
        \see positionChanged
     */
    Q_PROPERTY(float position READ position WRITE setPosition NOTIFY positionChanged)

    /*!
        \brief Current seekable status
        \see seekable
        \see seekableChanged
     */
    Q_PROPERTY(bool seekable READ seekable NOTIFY seekableChanged)

    /*!
        \brief Current state
        \see state
        \see stateChanged
     */
    Q_PROPERTY(int state READ state NOTIFY stateChanged)

    /*!
        \brief Current media time
        \see time
        \see setTime
        \see timeChanged
     */
    Q_PROPERTY(qint64 time READ time WRITE setTime NOTIFY timeChanged)

    /*!
        \brief Current media URL
        \see url
        \see setUrl
        \see urlChanged
     */
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

    /*!
        \brief Current volume
        \see volume
        \see setVolume
        \see volumeChanged
     */
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)


public:
    /*!
        \brief VlcQmlPlayer constructor
        \param parent parent object
     */
    explicit VlcQmlPlayer(QObject *parent = 0);
    ~VlcQmlPlayer();


    /*!
        \brief Pause current playback

        Invokable from QML.
     */
    Q_INVOKABLE void pause();

    /*!
        \brief Play current playback

        Invokable from QML.
     */
    Q_INVOKABLE void play();

    /*!
        \brief Stop current playback

        Invokable from QML.
     */
    Q_INVOKABLE void stop();


    /*!
        \brief Get current autoplay setting
        \return current autoplay setting

        Used as property in QML.
     */
    bool autoplay() const;

    /*!
        \brief Set autoplay setting
        \param autoplay new autoplay setting

        Used as property in QML.
     */
    void setAutoplay(bool autoplay);

    /*!
        \brief Get current deinterlacing mode
        \return current deinterlacing mode

        Used as property in QML.
     */
    int deinterlacing() const;

    /*!
        \brief Set deinterlacing mode
        \param deinterlacing new deinterlacing mode

        Used as property in QML.
     */
    void setDeinterlacing(int deinterlacing);

    /*!
        \brief Get current media length
        \return current media length

        Used as property in QML.
     */
    qint64 length() const;

    /*!
        \brief Get current media position
        \return current media position from 0 to 1

        Used as property in QML.
     */
    float position() const;

    /*!
        \brief Set current media position
        \param position media position from 0 to 1

        Used as property in QML.
     */
    void setPosition(float position);

    /*!
        \brief Get current seekable status
        \return current seekable status

        Used as property in QML.
     */
    bool seekable() const;

    /*!
        \brief Get current state
        \return current state

        Used as property in QML.
     */
    int state() const;

    /*!
        \brief Get current media time
        \return current media time

        Used as property in QML.
     */
    qint64 time() const;

    /*!
        \brief Set current media time
        \param time current media time

        Used as property in QML.
     */
    void setTime(qint64 time);

    /*!
        \brief Get current media URL
        \return current media URL

        Used as property in QML.
     */
    QUrl url() const;

    /*!
        \brief Set media URL
        \param url new media URL

        Used as property in QML.
     */
    void setUrl(const QUrl &url);

    /*!
        \brief Get current volume
        \return current volume (int)

        Used as property in QML.
     */
    int volume() const;

    /*!
        \brief Set volume
        \param volume new volume

        Used as property in QML.
     */
    void setVolume(int volume);


signals:
    /*!
        \brief Autoplay changed signal
    */
    void autoplayChanged();

    /*!
        \brief Deinterlacing changed signal
    */
    void deinterlacingChanged();

    /*!
        \brief Length changed signal
    */
    void lengthChanged();

    /*!
        \brief Position changed signal
    */
    void positionChanged();

    /*!
        \brief Seekable changed signal
    */
    void seekableChanged();

    /*!
        \brief State changed signal
    */
    void stateChanged();

    /*!
        \brief Time changed signal
    */
    void timeChanged();

    /*!
        \brief URL changed signal
    */
    void urlChanged();

    /*!
        \brief Volume changed signal
    */
    void volumeChanged();


private slots:
    void mediaParsed(bool parsed);
    void mediaPlayerVout(int count);

private:
    void openInternal();

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

    bool _autoplay;
    Vlc::Deinterlacing _deinterlacing;
};

#endif // VLCQT_QMLPLAYER_H_
