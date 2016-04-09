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
class VlcTrackModel;

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
        \brief Current log level
        \see logLevel
        \see setLogLevel
        \see logLevelChanged
     */
    Q_PROPERTY(int logLevel READ logLevel WRITE setLogLevel NOTIFY logLevelChanged)

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

    /*!
        \brief Audio track model
        \see audioTrackModel
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(VlcTrackModel *audioTrackModel READ audioTrackModel CONSTANT)

    /*!
        \brief Current audio track
        \see audioTrack
        \see setAudioTrack
        \see audioTrackChanged
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(int audioTrack READ audioTrack WRITE setAudioTrack NOTIFY audioTrackChanged)

    /*!
        \brief Current audio preferred languages
        \see audioPreferredLanguages
        \see setAudioPreferredLanguages
        \see audioPreferredLanguagesChanged
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(QStringList audioPreferredLanguages READ audioPreferredLanguages WRITE setAudioPreferredLanguages NOTIFY audioPreferredLanguagesChanged)

    /*!
        \brief Subtitle track model
        \see subtitleTrackModel
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(VlcTrackModel *subtitleTrackModel READ subtitleTrackModel CONSTANT)

    /*!
        \brief Current subtitle track
        \see subtitleTrack
        \see setSubtitleTrack
        \see subtitleTrackChanged
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(int subtitleTrack READ subtitleTrack WRITE setSubtitleTrack NOTIFY subtitleTrackChanged)

    /*!
        \brief Current subtitle preferred languages
        \see subtitlePreferredLanguages
        \see setSubtitlePreferredLanguages
        \see subtitlePreferredLanguagesChanged
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(QStringList subtitlePreferredLanguages READ subtitlePreferredLanguages WRITE setSubtitlePreferredLanguages NOTIFY subtitlePreferredLanguagesChanged)

    /*!
        \brief Video track model
        \see videoTrackModel
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(VlcTrackModel *videoTrackModel READ videoTrackModel CONSTANT)

    /*!
        \brief Current video track
        \see videoTrack
        \see setVideoTrack
        \see videoTrackChanged
        \since VLC-Qt 1.1
     */
    Q_PROPERTY(int videoTrack READ videoTrack WRITE setVideoTrack NOTIFY videoTrackChanged)


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
        \brief Get current log level
        \return current log level

        Used as property in QML.
     */
    int logLevel() const;

    /*!
        \brief Set log level
        \param level log level

        Used as property in QML.
     */
    void setLogLevel(int level);

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

    /*!
        \brief Get audio track model
        \return audio track model poiner

        Used as property in QML.
     */
    VlcTrackModel *audioTrackModel() const;

    /*!
        \brief Get current audio track
        \return the id of current audio track, or -1 if none

        Used as property in QML.
     */
    int audioTrack() const;

    /*!
        \brief Set current audio track
        \param audioTrack new audio track

        Used as property in QML.
     */
    void setAudioTrack(int audioTrack);

    /*!
        \brief Get preferred audio languages
        \return preferred languages

        Used as property in QML.
     */
    QStringList audioPreferredLanguages() const;

    /*!
        \brief Set preferred audio language
        \param audioPreferredLanguages preferred languages

        Used as property in QML.
     */
    void setAudioPreferredLanguages(const QStringList &audioPreferredLanguages);

    /*!
        \brief Get subtitle track model
        \return subtitle track model poiner

        Used as property in QML.
     */
    VlcTrackModel *subtitleTrackModel() const;

    /*!
        \brief Get current subtitle track
        \return the id of current subtitle track, or -1 if none

        Used as property in QML.
     */
    int subtitleTrack() const;

    /*!
        \brief Set current subtitle track
        \param subtitleTrack new subtitle track

        Used as property in QML.
     */
    void setSubtitleTrack(int subtitleTrack);

    /*!
        \brief Get preferred subtitle languages
        \return preferred languages

        Used as property in QML.
     */
    QStringList subtitlePreferredLanguages() const;

    /*!
        \brief Set preferred subtitle languages
        \param subtitlePreferredLanguages preferred languages, empty if disabled

        Used as property in QML.
     */
    void setSubtitlePreferredLanguages(const QStringList &subtitlePreferredLanguages);

    /*!
        \brief Get video track model
        \return video track model poiner

        Used as property in QML.
     */
    VlcTrackModel *videoTrackModel() const;

    /*!
        \brief Get current video track
        \return the id of current video track, or -1 if none

        Used as property in QML.
     */
    int videoTrack() const;

    /*!
        \brief Set current video track
        \param videoTrack new video track

        Used as property in QML.
     */
    void setVideoTrack(int videoTrack);


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
        \brief Log level changed signal
    */
    void logLevelChanged();

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

    /*!
        \brief Audio track changed signal
    */
    void audioTrackChanged();

    /*!
        \brief Audio preferred language changed signal
    */
    void audioPreferredLanguagesChanged();

    /*!
        \brief Subtitle track changed signal
    */
    void subtitleTrackChanged();

    /*!
        \brief Subtitle preferred language changed signal
    */
    void subtitlePreferredLanguagesChanged();

    /*!
        \brief Video track changed signal
    */
    void videoTrackChanged();


private slots:
    void mediaParsed(bool parsed);
    void mediaPlayerVout(int count);

private:
    void openInternal();
    int preferredAudioTrackId();
    int preferredSubtitleTrackId();

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;

    bool _autoplay;
    Vlc::Deinterlacing _deinterlacing;

    VlcTrackModel *_audioTrackModel;
    VlcTrackModel *_subtitleTrackModel;
    VlcTrackModel *_videoTrackModel;

    QStringList _audioPreferredLanguages;
    QStringList _subtitlePreferredLanguages;
};

#endif // VLCQT_QMLPLAYER_H_
