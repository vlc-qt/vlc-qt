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

#ifndef VLCQT_QMLVIDEOPLAYER_H_
#define VLCQT_QMLVIDEOPLAYER_H_

#include <QtQuick/QQuickItem>

#include "QmlVideoObject.h"
#include "SharedExportQml.h"

#include "TracksModel.h"

class VlcAudio;
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcVideo;

/*!
    \defgroup VLCQtQml VLC-Qt Qml (VLCQtQml)
    \brief QML classes for controlling video and media playback
 */

/*!
    \class VlcQmlVideoPlayer QmlVideoPlayer.h VLCQtQml/QmlVideoPlayer.h
    \ingroup VLCQtQml
    \brief QML video player

    A simple QML video player that can be used standalone and directly inside QML.
 */
class VLCQT_QML_EXPORT VlcQmlVideoPlayer : public VlcQmlVideoObject
{
Q_OBJECT
public:
    /*!
        \brief Current volume
        \see setVolume
        \see volumeChanged
     */
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

    /*!
        \brief Current aspect ratio
        \see setAspectRatio
     */
    Q_PROPERTY(QString aspectRatio READ aspectRatio WRITE setAspectRatio)

    /*!
        \brief Current crop ratio
        \see setCropRatio
     */
    Q_PROPERTY(QString cropRatio READ cropRatio WRITE setCropRatio)

    /*!
        \brief Current deinterlacing mode
        \see setDeinterlacing
     */
    Q_PROPERTY(QString deinterlacing READ deinterlacing WRITE setDeinterlacing)

    /*!
        \brief Current media URL
        \see setUrl
     */
    Q_PROPERTY(QUrl url READ url WRITE setUrl)

    /*!
        \brief Current autoplay setting
        \see setAutoplay
     */
    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay)

    /*!
        \brief Current state
        \see stateChanged
     */
    Q_PROPERTY(int state READ state NOTIFY stateChanged)

    /*!
        \brief Current seekable status
        \see seekableChanged
     */
    Q_PROPERTY(bool seekable READ seekable NOTIFY seekableChanged)

    /*!
        \brief Current media length
        \see length
        \see lengthChanged
     */
    Q_PROPERTY(int length READ length NOTIFY lengthChanged)

    /*!
        \brief Current media time
        \see time
        \see timeChanged
     */
    Q_PROPERTY(int time READ time WRITE setTime NOTIFY timeChanged)

    /*!
        \brief Current media position
        \see position
        \see positionChanged
     */
    Q_PROPERTY(float position READ position WRITE setPosition NOTIFY positionChanged)

    /*!
        \brief Current audio track
        \see audioTrack
        \see audioTrackChanged
     */
    Q_PROPERTY(int audioTrack READ audioTrack WRITE setAudioTrack NOTIFY audioTrackChanged)

    /*!
        \brief Audio tracks model
        \see audioTracksModel
     */
    Q_PROPERTY(TracksModel *audioTracksModel READ audioTracksModel CONSTANT)

    /*!
        \brief Current subtitle track
        \see subtitleTrack
        \see subtitleTrackChanged
     */
    Q_PROPERTY(int subtitleTrack READ subtitleTrack WRITE setSubtitleTrack NOTIFY subtitleTrackChanged)

    /*!
        \brief Subtitle tracks model
        \see subtitleTracksModel
     */
    Q_PROPERTY(TracksModel *subtitleTracksModel READ subtitleTracksModel CONSTANT)

    /*!
        \brief Current video track
        \see videoTrack
        \see videoTrackChanged
     */
    Q_PROPERTY(int videoTrack READ videoTrack WRITE setVideoTrack NOTIFY videoTrackChanged)

    /*!
        \brief Video tracks model
        \see videoTracksModel
     */
    Q_PROPERTY(TracksModel *videoTracksModel READ videoTracksModel CONSTANT)

    /*!
        \brief VlcQmlVideoPlayer constructor.
        \param parent parent item (QQuickItem *)
     */
    explicit VlcQmlVideoPlayer(QQuickItem *parent = 0);

    /*!
        VlcMediaPlayer destructor
     */
    ~VlcQmlVideoPlayer();


    /*!
        \brief Register QML plugin as VLCQt.VlcVideoPlayer

        Include into QML file as
        import VLCQt VERSION_MAJOR.VERSION_MINOR

        Object name: VlcVideoPlayer
     */
    static void registerPlugin();

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
        \brief Get current aspect ratio
        \return current aspect ratio

        Used as property in QML.
     */
    QString aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio

        Used as property in QML.
     */
    void setAspectRatio(const QString &aspectRatio);

    /*!
        \brief Get current crop ratio
        \return current crop ratio

        Used as property in QML.
     */
    QString cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio

        Used as property in QML.
     */
    void setCropRatio(const QString &cropRatio);

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
        \brief Get current deinterlacing() mode
        \return current deinterlacing mode

        Used as property in QML.
     */
    QString deinterlacing() const;

    /*!
        \brief Set deinterlacing mode
        \param deinterlacing new deinterlacing mode

        Used as property in QML.
     */
    void setDeinterlacing(const QString &deinterlacing);

    /*!
        \brief Get current state
        \return current state

        Used as property in QML.
     */
    int state() const;

    /*!
        \brief Get current seekable status
        \return current seekable status

        Used as property in QML.
     */
    bool seekable() const;

    /*!
        \brief Get current media length
        \return current media length

        Used as property in QML.
     */
    int length() const;

    /*!
        \brief Get current media time
        \return current media time

        Used as property in QML.
     */
    int time() const;

    /*!
        \brief Set current media time
        \param time current media time

        Used as property in QML.
     */
    void setTime(int time);

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
        \brief Get current audio track.
        \return the id of current audio track, or -1 if none (const int)

        Used as property in QML.
     */
    int audioTrack() const;

    /*!
        \brief Set current audio track.
        \param audioTrack new audio track (int)

        Used as property in QML.
     */
    void setAudioTrack(int audioTrack);

    /*!
        \brief Get audio tracks model.
        \return audio tracks model poiner(const TracksModel*)

        Used as property in QML.
     */
    TracksModel *audioTracksModel() const;

    /*!
        \brief Get current subtitle track.
        \return the id of current subtitle track, or -1 if none (const int)

        Used as property in QML.
     */
    int subtitleTrack() const;

    /*!
        \brief Set current subtitle track.
        \param subtitleTrack new subtitle track (int)

        Used as property in QML.
     */
    void setSubtitleTrack(int subtitleTrack);

    /*!
        \brief Get subtitle tracks model.
        \return subtitle tracks model poiner(const TracksModel*)

        Used as property in QML.
     */
    TracksModel *subtitleTracksModel() const;

    /*!
        \brief Get current video track.
        \return the id of current video track, or -1 if none (const int)

        Used as property in QML.
     */
    int videoTrack() const;

    /*!
        \brief Set current video track.
        \param videoTrack new video track (int)

        Used as property in QML.
     */
    void setVideoTrack(int videoTrack);

    /*!
        \brief Get video tracks model.
        \return video tracks model poiner(const TracksModel*)

        Used as property in QML.
     */
    TracksModel *videoTracksModel() const;

signals:
    /*!
        \brief Volume changed signal
    */
    void volumeChanged();

    /*!
        \brief State changed signal
    */
    void stateChanged();

    /*!
        \brief Seekable status changed signal
    */
    void seekableChanged();

    /*!
        \brief Length changed signal
    */
    void lengthChanged();

    /*!
        \brief Time changed signal
    */
    void timeChanged();

    /*!
        \brief Position changed signal
    */
    void positionChanged();

    /*!
        \brief Audio track changed signal
    */
    void audioTrackChanged();

    /*!
        \brief Subtitle track changed signal
    */
    void subtitleTrackChanged();

    /*!
        \brief Video track changed signal
    */
    void videoTrackChanged();

private slots:
    void seekableChangedPrivate(bool);
    void mediaParsed(int);
    void mediaPlayerVout(int);
private:
    void openInternal();

    VlcInstance *_instance;
    VlcMedia *_media;

    VlcAudio *_audioManager;
    VlcVideo *_videoManager;

    Vlc::Deinterlacing _deinterlacing;

    bool _hasMedia;
    bool _autoplay;
    bool _seekable;

    TracksModel *_audioTracksModel;
    TracksModel *_subtitleTracksModel;
    TracksModel *_videoTracksModel;
};

#endif // VLCQT_QMLVIDEOPLAYER_H_
