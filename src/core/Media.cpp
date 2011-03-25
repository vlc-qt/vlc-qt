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

#include <QtCore/QDebug>

#include <vlc/vlc.h>

#include "core/Error.h"
#include "core/Instance.h"
#include "core/Media.h"

VlcMedia::VlcMedia(const QString &location,
				   QObject *parent)
	: QObject(parent)
{
	// Create a new libvlc media descriptor from location
	_vlcMedia = libvlc_media_new_location(_vlcInstance, location.toAscii().data());
	VlcError::errmsg();
	qDebug() << "libvlc" << "Media:" << location;
}

VlcMedia::VlcMedia(libvlc_media_t *media,
				   QObject *parent)
	: QObject(parent)
{
	// Create a new libvlc media descriptor from existing one
	_vlcMedia = libvlc_media_duplicate(media);
	VlcError::errmsg();
}

VlcMedia::~VlcMedia()
{
	libvlc_media_release(_vlcMedia);

	VlcError::errmsg();
}

libvlc_media_t *VlcMedia::libvlcMedia()
{
	return _vlcMedia;
}
