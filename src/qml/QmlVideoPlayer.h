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

class VLCQT_QML_EXPORT VlcQmlVideoPlayer : public VlcQmlVideoObject
{
Q_OBJECT
public:
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int aspectRatio READ aspectRatio WRITE setAspectRatio)
    Q_PROPERTY(int cropRatio READ cropRatio WRITE setCropRatio)
    Q_PROPERTY(int deinterlacing READ deinterlacing WRITE setDeinterlacing)
    Q_PROPERTY(QUrl url READ url WRITE setUrl)
    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay)
    Q_PROPERTY(int state READ state NOTIFY stateChanged)

    explicit VlcQmlVideoPlayer(QQuickItem *parent = 0);
    ~VlcQmlVideoPlayer();

	Q_INVOKABLE void close();
	Q_INVOKABLE void openFile(const QString &file);
	Q_INVOKABLE void openStream(const QString &stream);
	Q_INVOKABLE void pause();
	Q_INVOKABLE void play();
	Q_INVOKABLE void stop();

	int volume() const;
    void setVolume(int volume);

    int aspectRatio();
    void setAspectRatio(int aspectRatio);

    int cropRatio();
    void setCropRatio(int cropRatio);

    QUrl url() const;
    void setUrl(const QUrl &url);

    bool autoplay() const;
    void setAutoplay(bool autoplay);

    int deinterlacing() const;
    void setDeinterlacing(int deinterlacing);

    int state() const;

signals:
    void volumeChanged();
    void stateChanged();

private:
    void openInternal();

    VlcInstance *_instance;
    VlcMediaPlayer *_player;
    VlcMedia *_media;

    VlcAudio *_audioManager;

    Vlc::Deinterlacing _deinterlacing;

    bool _hasMedia;
    bool _autoplay;
};

#endif // VLCQT_QMLVIDEOPLAYER_H_
