/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Media.cpp: Media manager
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

#include "core/Error.h"
#include "core/Instance.h"
#include "core/Media.h"

VlcMedia::VlcMedia(const QString &location,
				   QObject *parent) :
    QObject(parent)
{
	// Create a new libvlc media descriptor from location
	_vlcMedia = libvlc_media_new_location(_vlcInstance, location.toAscii().data());
	VlcError::errmsg();
	qDebug() << "libvlc" << "Media:" << location;
}

VlcMedia::VlcMedia(libvlc_media_t *media,
				   QObject *parent) :
	QObject(parent)
{
	// Create a new libvlc media descriptor from existing one
	_vlcMedia = media;
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
