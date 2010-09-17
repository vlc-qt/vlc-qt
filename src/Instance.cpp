/****************************************************************************
* VLC-Qt - Qt and libVLC connector library
* Instance.cpp: Main libVLC instance
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

#include <QtCore/QDebug>
#include <QtGui/QMessageBox>

#include "Config.h"
#include "Instance.h"

libvlc_instance_t * _vlcInstance = NULL;
libvlc_media_player_t * _vlcCurrentMediaPlayer = NULL;

VlcInstance::VlcInstance(const QList<const char *> &args,
						 const WId &widget,
						 QObject *parent) :
	QObject(parent),
	_vlcMedia(NULL),
	_widgetId(widget)
{
	_check = new QTimer(this);
	connect(_check, SIGNAL(timeout()), this, SLOT(checkPlayingState()));
	_check->start(300);

	const char *vlcArgs[args.size()];
	for(int i=0; i<args.size(); i++)
		vlcArgs[i] = args[i];

	_vlcInstance = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);

	checkError();

	if(_vlcInstance) {
		qDebug() << "libvlc-qt" << version() << "initialised";
		qDebug() << "Using libVLC version:" << libvlc_get_version();
		qDebug() << "libVLC loaded";
	} else {
		qDebug() << "libvlc-qt Error: libVLC failed to load!";
		switch(fatalError()) {
		case QMessageBox::Ok:
			exit(-100);
			break;
		default:
			break;
		};
	}
}

VlcInstance::~VlcInstance()
{
	delete _check;

	libvlc_release(_vlcInstance);
}

QString VlcInstance::version()
{
#ifdef LIBVLCQT_VERSION
	return QString(LIBVLCQT_VERSION);
#else
	return QString("Unknown");
#endif //LIBVLCQT_VERSION
}

QString VlcInstance::libVlcVersion()
{
	return QString(libvlc_get_version());
}

void VlcInstance::open(const QString &media)
{
	unloadMedia();

	/* Create a new LibVLC media descriptor */
	_vlcMedia = libvlc_media_new_location(_vlcInstance, media.toAscii());
	checkError();
	qDebug() << "libVlc" <<"Media:" << media;

	_vlcCurrentMediaPlayer = libvlc_media_player_new_from_media(_vlcMedia);
	checkError();


	/* Disable mouse and keyboard events */
	libvlc_video_set_key_input(_vlcCurrentMediaPlayer, false);
	//libvlc_video_set_mouse_input(_vlcCurrentMediaPlayer, false);


	/* Get our media instance to use our window */
	if (_vlcCurrentMediaPlayer) {
#if defined(Q_WS_WIN)
		libvlc_media_player_set_hwnd(_vlcCurrentMediaPlayer, _widgetId);
#elif defined(Q_WS_MAC)
		libvlc_media_player_set_agl(_vlcCurrentMediaPlayer, _widgetId);
#else // Q_WS_X11
		libvlc_media_player_set_xwindow(_vlcCurrentMediaPlayer, _widgetId);
#endif // Q_WS_*

		checkError();
	}

	play();
}

void VlcInstance::unloadMedia()
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_media_player_release(_vlcCurrentMediaPlayer);
		_vlcCurrentMediaPlayer = NULL;
	}

	if (_vlcMedia) {
		libvlc_media_release(_vlcMedia);
		_vlcMedia = NULL;
	}

	checkError();
}

void VlcInstance::play()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	libvlc_media_player_play(_vlcCurrentMediaPlayer);
	checkError();
}

void VlcInstance::pause()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	if(libvlc_media_player_can_pause(_vlcCurrentMediaPlayer) == 1)
		libvlc_media_player_pause(_vlcCurrentMediaPlayer);
	checkError();
}

void VlcInstance::stop()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return;

	libvlc_media_player_stop(_vlcCurrentMediaPlayer);
	unloadMedia();
	checkError();
}

void VlcInstance::checkPlayingState()
{
	if(_vlcCurrentMediaPlayer == NULL) {
		emit state(false, false, false);
		return;
	}

	bool playing;
	bool audio_count;
	bool video_count;

	playing = libvlc_media_player_get_state(_vlcCurrentMediaPlayer) == libvlc_Playing;
	audio_count = libvlc_audio_get_track_count(_vlcCurrentMediaPlayer) > 0;
	video_count = libvlc_video_get_track_count(_vlcCurrentMediaPlayer) > 0;

	emit state(playing, audio_count, video_count);
}

void VlcInstance::checkError()
{
	if(libvlc_errmsg()) {
		qDebug() << "libVLC" << "Error:" << libvlc_errmsg();
		libvlc_clearerr();
	}
}

bool VlcInstance::isActive()
{
	if(_vlcCurrentMediaPlayer == NULL)
		return false;

	// It's possible that the vlc doesn't play anything
	// so check before
	libvlc_media_t *curMedia;
	curMedia = libvlc_media_player_get_media(_vlcCurrentMediaPlayer);

	if (curMedia == NULL)
		return false;

	libvlc_state_t state;
	state = libvlc_media_player_get_state(_vlcCurrentMediaPlayer);

	if(state == libvlc_NothingSpecial || state == libvlc_Ended || state == libvlc_Error)
		return false;
	else
		return true;
}

int VlcInstance::fatalError() const
{
	 int ret = QMessageBox::critical(0, "libVLC Initialization",
									"libVLC could not be initialized successfully.\n"
									"The application will now exit.",
									QMessageBox::Ok | QMessageBox::Cancel,
									QMessageBox::Ok);
	 return ret;
}
