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

class VlcAudio;
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcVideo;

/*!
    \class VlcQmlVideoPlayer QmlVideoPlayer.h vlc-qt/QmlVideoPlayer.h
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
    Q_PROPERTY(int aspectRatio READ aspectRatio WRITE setAspectRatio)

    /*!
        \brief Current crop ratio
        \see setCropRatio
     */
    Q_PROPERTY(int cropRatio READ cropRatio WRITE setCropRatio)

    /*!
        \brief Current deinterlacing mode
        \see setDeinterlacing
     */
    Q_PROPERTY(int deinterlacing READ deinterlacing WRITE setDeinterlacing)

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
        \param volume new volume (int)

        Used as property in QML.
     */
    void setVolume(int volume);

    /*!
        \brief Get current aspect ratio
        \return current aspect ratio (int)

        Used as property in QML.
     */
    int aspectRatio();

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio (int)

        Used as property in QML.
     */
    void setAspectRatio(int aspectRatio);

    /*!
        \brief Get current crop ratio
        \return current crop ratio (int)

        Used as property in QML.
     */
    int cropRatio();

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio (int)

        Used as property in QML.
     */
    void setCropRatio(int cropRatio);

    /*!
        \brief Get current media URL
        \return current media URL (QUrl)

        Used as property in QML.
     */
    QUrl url() const;

    /*!
        \brief Set media URL
        \param url new media URL (QUrl)

        Used as property in QML.
     */
    void setUrl(const QUrl &url);

    /*!
        \brief Get current autoplay setting
        \return current autoplay setting (bool)

        Used as property in QML.
     */
    bool autoplay() const;

    /*!
        \brief Set autoplay setting
        \param autoplay new autoplay setting (bool)

        Used as property in QML.
     */
    void setAutoplay(bool autoplay);

    /*!
        \brief Get current deinterlacing() mode
        \return current deinterlacing mode (int)

        Used as property in QML.
     */
    int deinterlacing() const;

    /*!
        \brief Set deinterlacing mode
        \param deinterlacing new deinterlacing mode (int)

        Used as property in QML.
     */
    void setDeinterlacing(int deinterlacing);

    /*!
        \brief Get current state
        \return current state (int)

        Used as property in QML.
     */
    int state() const;

    /*!
        \brief Get current seekable status
        \return current seekable status (bool)

        Used as property in QML.
     */
    bool seekable() const;

    /*!
        \brief Get current media length
        \return current media length(int)

        Used as property in QML.
     */
    int length() const;

    /*!
        \brief Get current media time
        \return current media time(int)

        Used as property in QML.
     */
    int time() const;

    /*!
        \brief Set current media time
        \param current media time(int)

        Used as property in QML.
     */
    void setTime(int time);

    /*!
        \brief Get current media position
        \return current media position from 0 to 1(float)

        Used as property in QML.
     */
    float position() const;

    /*!
        \brief Set current media position
        \param position media position from 0 to 1(float)

        Used as property in QML.
     */
    void setPosition(float position);


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

private slots:
    void seekableChangedPrivate(bool);

private:
    void openInternal();

    VlcInstance *_instance;
    VlcMedia *_media;

    VlcAudio *_audioManager;

    Vlc::Deinterlacing _deinterlacing;

    bool _hasMedia;
    bool _autoplay;
    bool _seekable;
};

#endif // VLCQT_QMLVIDEOPLAYER_H_
