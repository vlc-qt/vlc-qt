/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Media.h: Media manager
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

#ifndef VLCQT_MEDIA_H_
#define VLCQT_MEDIA_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <vlc/vlc.h>

/*! \class VlcMedia Media.h vlc-qt/Media.h
	\brief Media item

	An abstract representation of a playable media.
	It consists of a media location and various optional meta data.
*/
class VlcMedia : public QObject
{
Q_OBJECT
public:
	/*!
		\brief Media constructor.

		\param location location of the media
		\param parent instance's parent object
	*/
	VlcMedia(const QString &location, QObject *parent = 0);

	/*!
		\brief Media constructor.

		\param widget unique ID of video widget
		\param media libvlc media item
	*/
	VlcMedia(libvlc_media_t *media, QObject *parent = 0);

	/*!
		\brief Media destructor
	*/
	~VlcMedia();

	/*!
		\brief libvlc media item

		\return libvlc_media_t item
	*/
	libvlc_media_t *libvlcMedia();

private:
	libvlc_media_t * _vlcMedia;

};

#endif // VLCQT_MEDIA_H_
