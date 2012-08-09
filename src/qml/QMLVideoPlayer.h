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

#ifndef VLCQT_QMLVIDEOPLAYER_H_
#define VLCQT_QMLVIDEOPLAYER_H_

#include <QtCore/QMutex>
#include <QtCore/QTimer>
#include <QtDeclarative/QDeclarativeItem>

class VlcAudio;
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class VlcQMLVideoPlayer : public QDeclarativeItem
{
Q_OBJECT
public:
	explicit VlcQMLVideoPlayer(QDeclarativeItem *parent = 0);
	~VlcQMLVideoPlayer();

	Q_INVOKABLE void close();
	Q_INVOKABLE void openFile(const QString &file);
	Q_INVOKABLE void openStream(const QString &stream);
	Q_INVOKABLE void pause();
	Q_INVOKABLE void play();
	Q_INVOKABLE void stop();

	QImage *_frame;
	QMutex _mutex;

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

private slots:
	void updateFrame();

private:
	void openInternal();

	VlcInstance *_instance;
	VlcMediaPlayer *_player;
	VlcMedia *_media;

	VlcAudio *_audioManager;

	bool _hasMedia;
	int _currentTime;
	QTimer *_timer;
};

#endif // VLCQT_QMLVIDEOPLAYER_H_
