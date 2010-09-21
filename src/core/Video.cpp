/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Video.cpp: libvlc video controls
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

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "core/Video.h"

QString VlcVideo::aspectRatio()
{
	QString ratio("");
	if (_vlcCurrentMediaPlayer) {
		ratio = libvlc_video_get_aspect_ratio(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return ratio;
}

QString VlcVideo::cropGeometry()
{
	QString crop("");
	if (_vlcCurrentMediaPlayer) {
		crop = libvlc_video_get_crop_geometry(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return crop;
}

void VlcVideo::setAspectRatio(const QString &ratio)
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, ratio.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setCropGeometry(const QString &crop)
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, crop.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setDeinterlace(const QString &filter)
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, filter.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setTeletextPage(const int &page)
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_video_set_teletext(_vlcCurrentMediaPlayer, page);
		VlcError::errmsg();
	}
}

int VlcVideo::teletextPage()
{
	int page = -1;
	if (_vlcCurrentMediaPlayer) {
		page = libvlc_video_get_teletext(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return page;
}

void VlcVideo::toggleTeletext()
{
	if (_vlcCurrentMediaPlayer) {
		libvlc_toggle_teletext(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}
}
