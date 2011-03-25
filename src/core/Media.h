/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_MEDIA_H_
#define VLCQT_MEDIA_H_

#include <QtCore/QObject>
#include <QtCore/QString>

struct libvlc_media_t;

/*!
	\class VlcMedia Media.h vlc-qt/Media.h
	\brief Media item

	An abstract representation of a playable media.
	It consists of a media location and various optional meta data.
*/
class VlcMedia : public QObject
{
Q_OBJECT
public:
	/*!
		\brief VlcMedia constructor.

		This constructor creates a new media instance from a media location.
		\param location location of the media (QString)
		\param parent instance's parent object (QObject)
	*/
	VlcMedia(const QString &location,
			 QObject *parent = 0);

	/*!
		\brief VlcMedia constructor.

		This constructor creates a new media instance from an existing one.
		\param media libvlc media item (libvlc_media_t)
		\param parent instance's parent object (QObject)
	*/
	VlcMedia(libvlc_media_t *media,
			 QObject *parent = 0);

	/*!
		\brief VlcMedia destructor
	*/
	~VlcMedia();

	/*!
		\brief libvlc media item

		\return libvlc media item (libvlc_media_t)
	*/
	libvlc_media_t *libvlcMedia();

private:
	libvlc_media_t * _vlcMedia;

};

#endif // VLCQT_MEDIA_H_
