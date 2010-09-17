/****************************************************************************
* VLC-Qt - Qt and libVLC connector library
* Instance.h: Main libVLC instance
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

#ifndef VLCQT_VLCINSTANCE_H_
#define VLCQT_VLCINSTANCE_H_

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

#include <vlc/vlc.h>

#include "Config.h"

extern libvlc_instance_t *_vlcInstance;
extern libvlc_media_player_t *_vlcCurrentMediaPlayer;

/*! \class Instance Instance.h vlc-qt/Instance.h
	\brief Main instance

	This class is basic Instance manager for VLC-Qt library.
	It provides main playback controls.
*/
class VlcInstance : public QObject
{
Q_OBJECT
public:
	/*!
		Instance constructor. This is mandatory to use VLC-Qt and all its other classes.
		\param args libVLC arguments
		\param widget unique ID of video widget
		\param parent instance's parent object
	*/
	VlcInstance(const QList<const char *> &args, const WId &widget = NULL, QObject *parent = NULL);

	/*!
		Instance destructor
	*/
	~VlcInstance();


	/*!
		Open media file or stream. Any media shoudl be playable and opened.
		\param media path or URL
	*/
	void open(const QString &media);

	/*!
		Check if player is currently playing any media
		\return true if instance is playing
	*/
	static bool isActive();

	/*!
		Error check
	*/
	static void checkError();

	/*!
		Version info
		\return version
	*/
	static QString version();

	/*!
		libVLC version info
		\return libVLC version
	*/
	static QString libVlcVersion();


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
	void state(const bool, const bool, const bool);


private slots:
	void checkPlayingState();

private:
	int fatalError() const;
	void unloadMedia();

	libvlc_media_t * _vlcMedia;
	WId _widgetId;

	QTimer *_check;
};

#endif // VLCQT_VLCINSTANCE_H_
