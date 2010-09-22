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
	QString ratio = "";
	if(_vlcCurrentMediaPlayer) {
		ratio = libvlc_video_get_aspect_ratio(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return ratio;
}

QString VlcVideo::cropGeometry()
{
	QString crop = "";
	if(_vlcCurrentMediaPlayer) {
		crop = libvlc_video_get_crop_geometry(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return crop;
}

void VlcVideo::setAspectRatio(const QString &ratio)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, ratio.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setCropGeometry(const QString &crop)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, crop.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setDeinterlace(const QString &filter)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, filter.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setSubtitle(const int &subtitle)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_spu(_vlcCurrentMediaPlayer, subtitle);
		VlcError::errmsg();
	}
}

void VlcVideo::setSubtitleFile(const QString &subtitle)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_subtitle_file(_vlcCurrentMediaPlayer, subtitle.toAscii().data());
		VlcError::errmsg();
	}
}

void VlcVideo::setTeletextPage(const int &page)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_teletext(_vlcCurrentMediaPlayer, page);
		VlcError::errmsg();
	}
}

void VlcVideo::setTrack(const int &track)
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_video_set_track(_vlcCurrentMediaPlayer, track);
		VlcError::errmsg();
	}
}

int VlcVideo::subtitle()
{
	int subtitle = -1;
	if(_vlcCurrentMediaPlayer) {
		subtitle = libvlc_video_get_spu(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return subtitle;
}

int VlcVideo::subtitleCount()
{
	int count = -1;
	if(_vlcCurrentMediaPlayer) {
		count = libvlc_video_get_spu_count(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return count;
}

QStringList VlcVideo::subtitleDescription()
{
	QStringList descriptions;

	if(_vlcCurrentMediaPlayer) {
		libvlc_track_description_t *desc;
		desc = libvlc_video_get_spu_description(_vlcCurrentMediaPlayer);
		VlcError::errmsg();

		descriptions << QString().fromUtf8(desc->psz_name);
		if(subtitleCount() > 1) {
			for(int i = 1; i < subtitleCount(); i++) {
				desc = desc->p_next;
				descriptions << QString().fromUtf8(desc->psz_name);
			}
		}
	}

	return descriptions;
}

int VlcVideo::teletextPage()
{
	int page = -1;
	if(_vlcCurrentMediaPlayer) {
		page = libvlc_video_get_teletext(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return page;
}

void VlcVideo::toggleTeletext()
{
	if(_vlcCurrentMediaPlayer) {
		libvlc_toggle_teletext(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}
}

int VlcVideo::track()
{
	int track = -1;
	if(_vlcCurrentMediaPlayer) {
		track = libvlc_video_get_track(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return track;
}

int VlcVideo::trackCount()
{
	int count = -1;
	if(_vlcCurrentMediaPlayer) {
		count = libvlc_video_get_track_count(_vlcCurrentMediaPlayer);
		VlcError::errmsg();
	}

	return count;
}

QStringList VlcVideo::trackDescription()
{
	QStringList descriptions;

	if(_vlcCurrentMediaPlayer) {
		libvlc_track_description_t *desc;
		desc = libvlc_video_get_track_description(_vlcCurrentMediaPlayer);
		VlcError::errmsg();

		descriptions << QString().fromUtf8(desc->psz_name);
		if(trackCount() > 1) {
			for(int i = 1; i < trackCount(); i++) {
				desc = desc->p_next;
				descriptions << QString().fromUtf8(desc->psz_name);
			}
		}
	}

	return descriptions;
}

QList<int> VlcVideo::trackIds()
{
	QList<int> ids;

	if(_vlcCurrentMediaPlayer) {
		libvlc_track_description_t *desc;
		desc = libvlc_video_get_track_description(_vlcCurrentMediaPlayer);
		VlcError::errmsg();

		ids << desc->i_id;
		if(trackCount() > 1) {
			for(int i = 1; i < trackCount(); i++) {
				desc = desc->p_next;
				ids << desc->i_id;
			}
		}
	}

	return ids;
}
