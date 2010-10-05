/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* MediaPlayer.h: MediaPlayer
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#ifndef VLCQT_MEDIAPLAYER_H_
#define VLCQT_MEDIAPLAYER_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/QWidget>
#include <vlc/vlc.h>

#include "Instance.h"
#include "Media.h"

extern libvlc_media_player_t *_vlcCurrentMediaPlayer;

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
		\param widget unique ID of video widget (WId)
		\param parent instance's parent object (QObject)
	*/
	VlcMediaPlayer(const WId &widget = NULL,
				   QObject *parent = NULL);

	/*!
		VlcMediaPlayer destructor
	*/
	~VlcMediaPlayer();

	/*!
		\brief Check if player is currently playing any media.
		\return true if instance is playing (bool)
	*/
	static bool isActive();

	/*!
		\brief Get the current movie lenght (in ms).
		\return the movie lenght (in ms), or -1 if there is no media (int)
	*/
	static int lenght();

	/*!
		\brief Open media file or stream. Any media should be playable and opened.
		\param media path or URL (QString)
	*/
	void open(const QString &media);

	/*! \brief Set the movie time (in ms).

		This has no effect if no media is being played. Not all formats and protocols support this.
		\param time the movie time (in ms) (int)
	*/
	static void setTime(const int &time);

	/*!
		\brief Get the current movie time (in ms).
		\return the movie time (in ms), or -1 if there is no media (int)
	*/
	static int time();


public slots:
	/*!
		Starts playing current media if possible
	*/
	void play();

	/*!
		Pauses the playback of current media if possible
	*/
	void pause();

	/*!
		Stops playing current media
	*/
	void stop();


signals:
	/*!
		Signal sending VLC-Qt state
		\param bool true if player is playing any media
		\param bool true if media has audio
		\param bool true if media has video
	*/
	void state(const bool,
			   const bool,
			   const bool);


private slots:
	void checkPlayingState();

private:
	void unloadMedia();

	VlcMedia *_vlcMedia;
	WId _widgetId;

	QTimer *_check;
};

#endif // VLCQT_MEDIAPLAYER_H_
